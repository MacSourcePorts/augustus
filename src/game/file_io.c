#include "file_io.h"

#include "building/barracks.h"
#include "building/count.h"
#include "building/granary.h"
#include "building/list.h"
#include "building/monument.h"
#include "building/storage.h"
#include "city/culture.h"
#include "city/data.h"
#include "core/file.h"
#include "core/log.h"
#include "city/message.h"
#include "city/view.h"
#include "core/dir.h"
#include "core/random.h"
#include "core/zip.h"
#include "empire/city.h"
#include "empire/empire.h"
#include "empire/trade_prices.h"
#include "empire/trade_route.h"
#include "figure/enemy_army.h"
#include "figure/formation.h"
#include "figure/name.h"
#include "figure/route.h"
#include "figure/trader.h"
#include "game/time.h"
#include "game/tutorial.h"
#include "map/aqueduct.h"
#include "map/bookmark.h"
#include "map/building.h"
#include "map/desirability.h"
#include "map/elevation.h"
#include "map/figure.h"
#include "map/image.h"
#include "map/property.h"
#include "map/random.h"
#include "map/routing.h"
#include "map/sprite.h"
#include "map/terrain.h"
#include "map/tiles.h"
#include "scenario/criteria.h"
#include "scenario/earthquake.h"
#include "scenario/emperor_change.h"
#include "scenario/gladiator_revolt.h"
#include "scenario/invasion.h"
#include "scenario/map.h"
#include "scenario/scenario.h"
#include "sound/city.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMPRESS_BUFFER_SIZE 3000000
#define UNCOMPRESSED 0x80000000

#define PIECE_SIZE_DYNAMIC 0

static const int SAVE_GAME_CURRENT_VERSION = 0x87;

static const int SAVE_GAME_LAST_ORIGINAL_LIMITS_VERSION = 0x66;
static const int SAVE_GAME_LAST_SMALLER_IMAGE_ID_VERSION = 0x76;
static const int SAVE_GAME_LAST_NO_DELIVERIES_VERSION = 0x77;
static const int SAVE_GAME_LAST_STATIC_VERSION = 0x78;
static const int SAVE_GAME_LAST_JOINED_IMPORT_EXPORT_VERSION = 0x79;
static const int SAVE_GAME_LAST_STATIC_BUILDING_COUNT_VERSION = 0x80;
static const int SAVE_GAME_LAST_STATIC_MONUMENT_DELIVERIES_VERSION = 0x81;
static const int SAVE_GAME_LAST_STORED_IMAGE_IDS = 0x83;
// SAVE_GAME_INCREASE_GRANARY_CAPACITY shall be updated if we decide to change granary capacity again.
static const int SAVE_GAME_INCREASE_GRANARY_CAPACITY = 0x85;
// static const int SAVE_GAME_ROADBLOCK_DATA_MOVED_FROM_SUBTYPE = 0x86; This define is unneeded for now
static const int SAVE_GAME_LAST_ORIGINAL_TERRAIN_DATA_SIZE_VERSION = 0x86;


static char compress_buffer[COMPRESS_BUFFER_SIZE];

typedef struct {
    buffer buf;
    int compressed;
    int dynamic;
} file_piece;

typedef struct {
    buffer *graphic_ids;
    buffer *edge;
    buffer *terrain;
    buffer *bitfields;
    buffer *random;
    buffer *elevation;
    buffer *random_iv;
    buffer *camera;
    buffer *scenario;
    buffer *end_marker;
} scenario_state;

static struct {
    int num_pieces;
    file_piece pieces[10];
    scenario_state state;
} scenario_data;

typedef struct {
    buffer *scenario_campaign_mission;
    buffer *file_version;
    buffer *image_grid;
    buffer *edge_grid;
    buffer *building_grid;
    buffer *terrain_grid;
    buffer *aqueduct_grid;
    buffer *figure_grid;
    buffer *bitfields_grid;
    buffer *sprite_grid;
    buffer *random_grid;
    buffer *desirability_grid;
    buffer *elevation_grid;
    buffer *building_damage_grid;
    buffer *aqueduct_backup_grid;
    buffer *sprite_backup_grid;
    buffer *figures;
    buffer *route_figures;
    buffer *route_paths;
    buffer *formations;
    buffer *formation_totals;
    buffer *city_data;
    buffer *city_faction_unknown;
    buffer *player_name;
    buffer *city_faction;
    buffer *buildings;
    buffer *city_view_orientation;
    buffer *game_time;
    buffer *building_extra_highest_id_ever;
    buffer *random_iv;
    buffer *city_view_camera;
    buffer *building_count_culture1;
    buffer *city_graph_order;
    buffer *emperor_change_time;
    buffer *empire;
    buffer *empire_cities;
    buffer *building_count_industry;
    buffer *trade_prices;
    buffer *figure_names;
    buffer *culture_coverage;
    buffer *scenario;
    buffer *max_game_year;
    buffer *earthquake;
    buffer *emperor_change_state;
    buffer *messages;
    buffer *message_extra;
    buffer *population_messages;
    buffer *message_counts;
    buffer *message_delays;
    buffer *building_list_burning_totals;
    buffer *figure_sequence;
    buffer *scenario_settings;
    buffer *invasion_warnings;
    buffer *scenario_is_custom;
    buffer *city_sounds;
    buffer *building_extra_highest_id;
    buffer *figure_traders;
    buffer *building_list_burning;
    buffer *building_list_small;
    buffer *building_list_large;
    buffer *tutorial_part1;
    buffer *building_count_military;
    buffer *enemy_army_totals;
    buffer *building_storages;
    buffer *building_count_culture2;
    buffer *building_count_support;
    buffer *tutorial_part2;
    buffer *gladiator_revolt;
    buffer *trade_route_limit;
    buffer *trade_route_traded;
    buffer *building_barracks_tower_sentry;
    buffer *building_extra_sequence;
    buffer *routing_counters;
    buffer *building_count_culture3;
    buffer *enemy_armies;
    buffer *city_entry_exit_xy;
    buffer *last_invasion_id;
    buffer *building_extra_corrupt_houses;
    buffer *scenario_name;
    buffer *bookmarks;
    buffer *tutorial_part3;
    buffer *city_entry_exit_grid_offset;
    buffer *end_marker;
    buffer *deliveries;
} savegame_state;

static struct {
    int num_pieces;
    file_piece pieces[100];
    savegame_state state;
} savegame_data;

static void init_file_piece(file_piece *piece, int size, int compressed)
{
    piece->compressed = compressed;
    piece->dynamic = size == PIECE_SIZE_DYNAMIC;
    if (piece->dynamic) {
        buffer_init(&piece->buf, 0, 0);
    } else {
        void *data = malloc(size);
        memset(data, 0, size);
        buffer_init(&piece->buf, data, size);
    }
}

static buffer *create_scenario_piece(int size)
{
    file_piece *piece = &scenario_data.pieces[scenario_data.num_pieces++];
    init_file_piece(piece, size, 0);
    return &piece->buf;
}

static buffer *create_savegame_piece(int size, int compressed)
{
    file_piece *piece = &savegame_data.pieces[savegame_data.num_pieces++];
    init_file_piece(piece, size, compressed);
    return &piece->buf;
}

static void clear_savegame_pieces(void)
{
    for (int i = 0; i < savegame_data.num_pieces; i++) {
        buffer_reset(&savegame_data.pieces[i].buf);
        free(savegame_data.pieces[i].buf.data);
    }
    savegame_data.num_pieces = 0;
}

static void init_scenario_data(void)
{
    if (scenario_data.num_pieces > 0) {
        for (int i = 0; i < scenario_data.num_pieces; i++) {
            buffer_reset(&scenario_data.pieces[i].buf);
        }
        return;
    }
    scenario_state *state = &scenario_data.state;
    state->graphic_ids = create_scenario_piece(52488);
    state->edge = create_scenario_piece(26244);
    state->terrain = create_scenario_piece(52488);
    state->bitfields = create_scenario_piece(26244);
    state->random = create_scenario_piece(26244);
    state->elevation = create_scenario_piece(26244);
    state->random_iv = create_scenario_piece(8);
    state->camera = create_scenario_piece(8);
    state->scenario = create_scenario_piece(1720);
    state->end_marker = create_scenario_piece(4);
}

static void init_savegame_data(int version)
{
    clear_savegame_pieces();

    int multiplier = 1;
    int count_multiplier = 1;
    int burning_totals_size = 8;
    if (version > SAVE_GAME_LAST_ORIGINAL_LIMITS_VERSION) {
        multiplier = 5;
    }
    if (version > SAVE_GAME_LAST_STATIC_VERSION) {
        multiplier = PIECE_SIZE_DYNAMIC;
        burning_totals_size = 4;
    }

    if (version > SAVE_GAME_LAST_STATIC_BUILDING_COUNT_VERSION) {
        count_multiplier = PIECE_SIZE_DYNAMIC;
    }

    int image_grid_size = 52488 * (version > SAVE_GAME_LAST_SMALLER_IMAGE_ID_VERSION ? 2 : 1);
    int terrain_grid_size = 52488 * (version > SAVE_GAME_LAST_ORIGINAL_TERRAIN_DATA_SIZE_VERSION ? 2 : 1);
    int figures_size = 128000 * multiplier;
    int route_figures_size = 1200 * multiplier;
    int route_paths_size = 300000 * multiplier;
    int formations_size = 6400 * multiplier;
    int buildings_size = 256000 * multiplier;
    int building_list_burning_size = 1000 * multiplier;
    int building_list_small_size = 1000 * multiplier;
    int building_list_large_size = 4000 * multiplier;
    int building_storages_size = 6400 * multiplier;

    int building_count_culture1 = 132 * count_multiplier;
    int building_count_culture2 = 32 * count_multiplier;
    int building_count_culture3 = 40 * count_multiplier;
    int building_count_military = 16 * count_multiplier;
    int building_count_industry = 128 * count_multiplier;
    int building_count_support = 24 * count_multiplier;


    savegame_state *state = &savegame_data.state;
    state->scenario_campaign_mission = create_savegame_piece(4, 0);
    state->file_version = create_savegame_piece(4, 0);
    if (version <= SAVE_GAME_LAST_STORED_IMAGE_IDS) {
        state->image_grid = create_savegame_piece(image_grid_size, 1);
    }
    state->edge_grid = create_savegame_piece(26244, 1);
    state->building_grid = create_savegame_piece(52488, 1);
    state->terrain_grid = create_savegame_piece(terrain_grid_size, 1);
    state->aqueduct_grid = create_savegame_piece(26244, 1);
    state->figure_grid = create_savegame_piece(52488, 1);
    state->bitfields_grid = create_savegame_piece(26244, 1);
    state->sprite_grid = create_savegame_piece(26244, 1);
    state->random_grid = create_savegame_piece(26244, 0);
    state->desirability_grid = create_savegame_piece(26244, 1);
    state->elevation_grid = create_savegame_piece(26244, 1);
    state->building_damage_grid = create_savegame_piece(26244, 1);
    state->aqueduct_backup_grid = create_savegame_piece(26244, 1);
    state->sprite_backup_grid = create_savegame_piece(26244, 1);
    state->figures = create_savegame_piece(figures_size, 1);
    state->route_figures = create_savegame_piece(route_figures_size, 1);
    state->route_paths = create_savegame_piece(route_paths_size, 1);
    state->formations = create_savegame_piece(formations_size, 1);
    state->formation_totals = create_savegame_piece(12, 0);
    state->city_data = create_savegame_piece(36136, 1);
    state->city_faction_unknown = create_savegame_piece(2, 0);
    state->player_name = create_savegame_piece(64, 0);
    state->city_faction = create_savegame_piece(4, 0);
    state->buildings = create_savegame_piece(buildings_size, 1);
    state->city_view_orientation = create_savegame_piece(4, 0);
    state->game_time = create_savegame_piece(20, 0);
    state->building_extra_highest_id_ever = create_savegame_piece(8, 0);
    state->random_iv = create_savegame_piece(8, 0);
    state->city_view_camera = create_savegame_piece(8, 0);
    state->building_count_culture1 = create_savegame_piece(building_count_culture1, 0);
    state->city_graph_order = create_savegame_piece(8, 0);
    state->emperor_change_time = create_savegame_piece(8, 0);
    state->empire = create_savegame_piece(12, 0);
    state->empire_cities = create_savegame_piece(2706, 1);
    state->building_count_industry = create_savegame_piece(building_count_industry, 0);
    state->trade_prices = create_savegame_piece(128, 0);
    state->figure_names = create_savegame_piece(84, 0);
    state->culture_coverage = create_savegame_piece(60, 0);
    state->scenario = create_savegame_piece(1720, 0);
    state->max_game_year = create_savegame_piece(4, 0);
    state->earthquake = create_savegame_piece(60, 0);
    state->emperor_change_state = create_savegame_piece(4, 0);
    state->messages = create_savegame_piece(16000, 1);
    state->message_extra = create_savegame_piece(12, 0);
    state->population_messages = create_savegame_piece(10, 0);
    state->message_counts = create_savegame_piece(80, 0);
    state->message_delays = create_savegame_piece(80, 0);
    state->building_list_burning_totals = create_savegame_piece(burning_totals_size, 0);
    state->figure_sequence = create_savegame_piece(4, 0);
    state->scenario_settings = create_savegame_piece(12, 0);
    state->invasion_warnings = create_savegame_piece(3232, 1);
    state->scenario_is_custom = create_savegame_piece(4, 0);
    state->city_sounds = create_savegame_piece(8960, 0);
    state->building_extra_highest_id = create_savegame_piece(4, 0);
    state->figure_traders = create_savegame_piece(4804, 0);
    state->building_list_burning = create_savegame_piece(building_list_burning_size, 1);
    state->building_list_small = create_savegame_piece(building_list_small_size, 1);
    state->building_list_large = create_savegame_piece(building_list_large_size, 1);
    state->tutorial_part1 = create_savegame_piece(32, 0);
    state->building_count_military = create_savegame_piece(building_count_military, 0);
    state->enemy_army_totals = create_savegame_piece(20, 0);
    state->building_storages = create_savegame_piece(building_storages_size, 0);
    state->building_count_culture2 = create_savegame_piece(building_count_culture2, 0);
    state->building_count_support = create_savegame_piece(building_count_support, 0);
    state->tutorial_part2 = create_savegame_piece(4, 0);
    state->gladiator_revolt = create_savegame_piece(16, 0);
    state->trade_route_limit = create_savegame_piece(1280, 1);
    state->trade_route_traded = create_savegame_piece(1280, 1);
    state->building_barracks_tower_sentry = create_savegame_piece(4, 0);
    state->building_extra_sequence = create_savegame_piece(4, 0);
    state->routing_counters = create_savegame_piece(16, 0);
    state->building_count_culture3 = create_savegame_piece(building_count_culture3, 0);
    state->enemy_armies = create_savegame_piece(900, 0);
    state->city_entry_exit_xy = create_savegame_piece(16, 0);
    state->last_invasion_id = create_savegame_piece(2, 0);
    state->building_extra_corrupt_houses = create_savegame_piece(8, 0);
    state->scenario_name = create_savegame_piece(65, 0);
    state->bookmarks = create_savegame_piece(32, 0);
    state->tutorial_part3 = create_savegame_piece(4, 0);
    state->city_entry_exit_grid_offset = create_savegame_piece(8, 0);
    state->end_marker = create_savegame_piece(284, 0); // 71x 4-bytes emptiness
    if (version > SAVE_GAME_LAST_STATIC_MONUMENT_DELIVERIES_VERSION) {
        state->deliveries = create_savegame_piece(PIECE_SIZE_DYNAMIC, 0);
    } else if (version > SAVE_GAME_LAST_NO_DELIVERIES_VERSION) {
        state->deliveries = create_savegame_piece(3200, 0);
    }
}

static void scenario_load_from_state(scenario_state *file)
{
    map_image_load_state_legacy(file->graphic_ids);
    map_terrain_load_state(file->terrain, 0, file->graphic_ids, 1);
    map_property_load_state(file->bitfields, file->edge);
    map_random_load_state(file->random);
    map_elevation_load_state(file->elevation);
    city_view_load_scenario_state(file->camera);

    random_load_state(file->random_iv);

    scenario_load_state(file->scenario);

    buffer_skip(file->end_marker, 4);
}

static void scenario_save_to_state(scenario_state *file)
{
    map_image_save_state_legacy(file->graphic_ids);
    map_terrain_save_state_legacy(file->terrain);
    map_property_save_state(file->bitfields, file->edge);
    map_random_save_state(file->random);
    map_elevation_save_state(file->elevation);
    city_view_save_scenario_state(file->camera);

    random_save_state(file->random_iv);

    scenario_save_state(file->scenario);

    buffer_skip(file->end_marker, 4);
}

static void savegame_load_from_state(savegame_state *state, int version)
{
    scenario_settings_load_state(state->scenario_campaign_mission,
        state->scenario_settings,
        state->scenario_is_custom,
        state->player_name,
        state->scenario_name);

    scenario_load_state(state->scenario);
    scenario_map_init();

    map_building_load_state(state->building_grid, state->building_damage_grid);
    map_terrain_load_state(state->terrain_grid, version > SAVE_GAME_LAST_ORIGINAL_TERRAIN_DATA_SIZE_VERSION,
        version <= SAVE_GAME_LAST_STORED_IMAGE_IDS ? state->image_grid : 0,
        version <= SAVE_GAME_LAST_SMALLER_IMAGE_ID_VERSION);
    map_aqueduct_load_state(state->aqueduct_grid, state->aqueduct_backup_grid);
    map_figure_load_state(state->figure_grid);
    map_sprite_load_state(state->sprite_grid, state->sprite_backup_grid);
    map_property_load_state(state->bitfields_grid, state->edge_grid);
    map_random_load_state(state->random_grid);
    map_desirability_load_state(state->desirability_grid);
    map_elevation_load_state(state->elevation_grid);
    figure_load_state(state->figures, state->figure_sequence, version > SAVE_GAME_LAST_STATIC_VERSION);
    figure_route_load_state(state->route_figures, state->route_paths);
    formations_load_state(state->formations, state->formation_totals, version > SAVE_GAME_LAST_STATIC_VERSION);

    city_data_load_state(state->city_data,
        state->city_faction,
        state->city_faction_unknown,
        state->city_graph_order,
        state->city_entry_exit_xy,
        state->city_entry_exit_grid_offset,
        version > SAVE_GAME_LAST_JOINED_IMPORT_EXPORT_VERSION);

    building_load_state(state->buildings,
        state->building_extra_sequence,
        state->building_extra_corrupt_houses,
        version > SAVE_GAME_LAST_STATIC_VERSION,
        version);
    building_barracks_load_state(state->building_barracks_tower_sentry);
    city_view_load_state(state->city_view_orientation, state->city_view_camera);
    game_time_load_state(state->game_time);
    random_load_state(state->random_iv);
    building_count_load_state(state->building_count_industry,
        state->building_count_culture1,
        state->building_count_culture2,
        state->building_count_culture3,
        state->building_count_military,
        state->building_count_support,
        version > SAVE_GAME_LAST_STATIC_BUILDING_COUNT_VERSION);
    if (version < SAVE_GAME_INCREASE_GRANARY_CAPACITY) {
        building_granary_update_built_granaries_capacity();
    }

    scenario_emperor_change_load_state(state->emperor_change_time, state->emperor_change_state);
    empire_load_state(state->empire);
    empire_city_load_state(state->empire_cities);
    trade_prices_load_state(state->trade_prices);
    figure_name_load_state(state->figure_names);
    city_culture_load_state(state->culture_coverage);

    scenario_criteria_load_state(state->max_game_year);
    scenario_earthquake_load_state(state->earthquake);
    city_message_load_state(state->messages, state->message_extra,
        state->message_counts, state->message_delays,
        state->population_messages);
    sound_city_load_state(state->city_sounds);
    traders_load_state(state->figure_traders);

    building_list_load_state(state->building_list_small, state->building_list_large,
        state->building_list_burning, state->building_list_burning_totals,
        version > SAVE_GAME_LAST_STATIC_VERSION);

    tutorial_load_state(state->tutorial_part1, state->tutorial_part2, state->tutorial_part3);

    building_storage_load_state(state->building_storages, version > SAVE_GAME_LAST_STATIC_VERSION);
    scenario_gladiator_revolt_load_state(state->gladiator_revolt);
    trade_routes_load_state(state->trade_route_limit, state->trade_route_traded);
    map_routing_load_state(state->routing_counters);
    enemy_armies_load_state(state->enemy_armies, state->enemy_army_totals);
    scenario_invasion_load_state(state->last_invasion_id, state->invasion_warnings);
    map_bookmark_load_state(state->bookmarks);

    buffer_skip(state->end_marker, 284);
    if (state) {
        buffer_skip(state->end_marker, 8);
    }
    if (version <= SAVE_GAME_LAST_NO_DELIVERIES_VERSION) {
        building_monument_initialize_deliveries();
    } else {
        building_monument_delivery_load_state(state->deliveries,
            version > SAVE_GAME_LAST_STATIC_MONUMENT_DELIVERIES_VERSION);
    }
    map_image_clear();
    map_image_update_all();
}

static void savegame_save_to_state(savegame_state *state)
{
    buffer_write_i32(state->file_version, SAVE_GAME_CURRENT_VERSION);

    scenario_settings_save_state(state->scenario_campaign_mission,
        state->scenario_settings,
        state->scenario_is_custom,
        state->player_name,
        state->scenario_name);

    map_building_save_state(state->building_grid, state->building_damage_grid);
    map_terrain_save_state(state->terrain_grid);
    map_aqueduct_save_state(state->aqueduct_grid, state->aqueduct_backup_grid);
    map_figure_save_state(state->figure_grid);
    map_sprite_save_state(state->sprite_grid, state->sprite_backup_grid);
    map_property_save_state(state->bitfields_grid, state->edge_grid);
    map_random_save_state(state->random_grid);
    map_desirability_save_state(state->desirability_grid);
    map_elevation_save_state(state->elevation_grid);

    figure_save_state(state->figures, state->figure_sequence);
    figure_route_save_state(state->route_figures, state->route_paths);
    formations_save_state(state->formations, state->formation_totals);

    city_data_save_state(state->city_data,
        state->city_faction,
        state->city_faction_unknown,
        state->city_graph_order,
        state->city_entry_exit_xy,
        state->city_entry_exit_grid_offset);

    building_save_state(state->buildings,
        state->building_extra_highest_id,
        state->building_extra_highest_id_ever,
        state->building_extra_sequence,
        state->building_extra_corrupt_houses);
    building_barracks_save_state(state->building_barracks_tower_sentry);
    city_view_save_state(state->city_view_orientation, state->city_view_camera);
    game_time_save_state(state->game_time);
    random_save_state(state->random_iv);
    building_count_save_state(state->building_count_industry,
        state->building_count_culture1,
        state->building_count_culture2,
        state->building_count_culture3,
        state->building_count_military,
        state->building_count_support);

    scenario_emperor_change_save_state(state->emperor_change_time, state->emperor_change_state);
    empire_save_state(state->empire);
    empire_city_save_state(state->empire_cities);
    trade_prices_save_state(state->trade_prices);
    figure_name_save_state(state->figure_names);
    city_culture_save_state(state->culture_coverage);

    scenario_save_state(state->scenario);

    scenario_criteria_save_state(state->max_game_year);
    scenario_earthquake_save_state(state->earthquake);
    city_message_save_state(state->messages, state->message_extra,
        state->message_counts, state->message_delays,
        state->population_messages);
    sound_city_save_state(state->city_sounds);
    traders_save_state(state->figure_traders);

    building_list_save_state(state->building_list_small, state->building_list_large,
        state->building_list_burning, state->building_list_burning_totals);

    tutorial_save_state(state->tutorial_part1, state->tutorial_part2, state->tutorial_part3);

    building_storage_save_state(state->building_storages);
    scenario_gladiator_revolt_save_state(state->gladiator_revolt);
    trade_routes_save_state(state->trade_route_limit, state->trade_route_traded);
    map_routing_save_state(state->routing_counters);
    enemy_armies_save_state(state->enemy_armies, state->enemy_army_totals);
    scenario_invasion_save_state(state->last_invasion_id, state->invasion_warnings);
    map_bookmark_save_state(state->bookmarks);

    buffer_skip(state->end_marker, 284);

    building_monument_delivery_save_state(state->deliveries);
}

int game_file_io_read_scenario(const char *filename)
{
    log_info("Loading scenario", filename, 0);
    init_scenario_data();
    FILE *fp = file_open(dir_get_file(filename, NOT_LOCALIZED), "rb");
    if (!fp) {
        return 0;
    }
    for (int i = 0; i < scenario_data.num_pieces; i++) {
        size_t read_size = fread(scenario_data.pieces[i].buf.data, 1, scenario_data.pieces[i].buf.size, fp);
        if (read_size != scenario_data.pieces[i].buf.size) {
            log_error("Unable to load scenario", filename, 0);
            file_close(fp);
            return 0;
        }
    }
    file_close(fp);

    scenario_load_from_state(&scenario_data.state);
    return 1;
}

int game_file_io_write_scenario(const char *filename)
{
    log_info("Saving scenario", filename, 0);
    init_scenario_data();
    scenario_save_to_state(&scenario_data.state);

    FILE *fp = file_open(filename, "wb");
    if (!fp) {
        log_error("Unable to save scenario", 0, 0);
        return 0;
    }
    for (int i = 0; i < scenario_data.num_pieces; i++) {
        fwrite(scenario_data.pieces[i].buf.data, 1, scenario_data.pieces[i].buf.size, fp);
    }
    file_close(fp);
    return 1;
}

static int read_int32(FILE *fp)
{
    uint8_t data[4];
    if (fread(&data, 1, 4, fp) != 4) {
        return 0;
    }
    buffer buf;
    buffer_init(&buf, data, 4);
    return buffer_read_i32(&buf);
}

static void write_int32(FILE *fp, int value)
{
    uint8_t data[4];
    buffer buf;
    buffer_init(&buf, data, 4);
    buffer_write_i32(&buf, value);
    fwrite(&data, 1, 4, fp);
}

static int read_compressed_chunk(FILE *fp, void *buffer, int bytes_to_read)
{
    if (bytes_to_read > COMPRESS_BUFFER_SIZE) {
        return 0;
    }
    int input_size = read_int32(fp);
    if ((unsigned int) input_size == UNCOMPRESSED) {
        if (fread(buffer, 1, bytes_to_read, fp) != bytes_to_read) {
            return 0;
        }
    } else {
        if (fread(compress_buffer, 1, input_size, fp) != input_size
            || !zip_decompress(compress_buffer, input_size, buffer, &bytes_to_read)) {
            return 0;
        }
    }
    return 1;
}

static int write_compressed_chunk(FILE *fp, const void *buffer, int bytes_to_write)
{
    if (bytes_to_write > COMPRESS_BUFFER_SIZE) {
        return 0;
    }
    int output_size = COMPRESS_BUFFER_SIZE;
    if (zip_compress(buffer, bytes_to_write, compress_buffer, &output_size)) {
        write_int32(fp, output_size);
        fwrite(compress_buffer, 1, output_size, fp);
    } else {
        // unable to compress: write uncompressed
        write_int32(fp, UNCOMPRESSED);
        fwrite(buffer, 1, bytes_to_write, fp);
    }
    return 1;
}

static int savegame_read_from_file(FILE *fp)
{
    for (int i = 0; i < savegame_data.num_pieces; i++) {
        file_piece *piece = &savegame_data.pieces[i];
        int result = 0;
        if (piece->dynamic) {
            int size = read_int32(fp);
            if (!size) {
                continue;
            }
            uint8_t *data = malloc(size);
            memset(data, 0, size);
            buffer_init(&piece->buf, data, size);
        }
        if (piece->compressed) {
            result = read_compressed_chunk(fp, piece->buf.data, piece->buf.size);
        } else {
            result = fread(piece->buf.data, 1, piece->buf.size, fp) == piece->buf.size;
        }
        // The last piece may be smaller than buf.size
        if (!result && i != (savegame_data.num_pieces - 1)) {
            log_info("Incorrect buffer size, got", 0, result);
            log_info("Incorrect buffer size, expected", 0, piece->buf.size);
            return 0;
        }
    }
    return 1;
}

static void savegame_write_to_file(FILE *fp)
{
    for (int i = 0; i < savegame_data.num_pieces; i++) {
        file_piece *piece = &savegame_data.pieces[i];
        if (piece->dynamic) {
            write_int32(fp, piece->buf.size);
            if (!piece->buf.size) {
                continue;
            }
        }
        if (piece->compressed) {
            write_compressed_chunk(fp, piece->buf.data, piece->buf.size);
        } else {
            fwrite(piece->buf.data, 1, piece->buf.size, fp);
        }
    }
}

static int get_savegame_version(FILE *fp)
{
    buffer buf;
    uint8_t data[4];
    buffer_init(&buf, data, 4);
    if (fseek(fp, 4, SEEK_CUR) ||
        fread(data, 1, 4, fp) != 4 ||
        fseek(fp, -8, SEEK_CUR)) {
        return 0;
    }
    return buffer_read_i32(&buf);
}

int game_file_io_read_saved_game(const char *filename, int offset)
{
    log_info("Loading saved game", filename, 0);
    FILE *fp = file_open(dir_get_file(filename, NOT_LOCALIZED), "rb");
    if (!fp) {
        log_error("Unable to load game, unable to open file.", 0, 0);
        return 0;
    }
    if (offset) {
        fseek(fp, offset, SEEK_SET);
    }
    int result = 0;
    int version = get_savegame_version(fp);
    if (version) {
        if (version > SAVE_GAME_CURRENT_VERSION) {
            log_error("Newer save game version than supported. Please update your Augustus. Version:", 0, version);
            return -1;
        }
        log_info("Savegame version", 0, version);
        init_savegame_data(version);
        result = savegame_read_from_file(fp);
    }
    file_close(fp);
    if (!result) {
        log_error("Unable to load game, unable to read savefile.", 0, 0);
        return 0;
    }
    savegame_load_from_state(&savegame_data.state, version);
    return 1;
}

int game_file_io_write_saved_game(const char *filename)
{
    init_savegame_data(SAVE_GAME_CURRENT_VERSION);

    log_info("Saving game", filename, 0);
    savegame_save_to_state(&savegame_data.state);

    FILE *fp = file_open(filename, "wb");
    if (!fp) {
        log_error("Unable to save game", 0, 0);
        return 0;
    }
    savegame_write_to_file(fp);
    file_close(fp);
    return 1;
}

int game_file_io_delete_saved_game(const char *filename)
{
    log_info("Deleting game", filename, 0);
    int result = file_remove(filename);
    if (!result) {
        log_error("Unable to delete game", 0, 0);
    }
    return result;
}
