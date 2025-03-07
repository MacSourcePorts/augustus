#ifndef TRANSLATION_TRANSLATION_H
#define TRANSLATION_TRANSLATION_H

#include "core/locale.h"

#include <stdint.h>

#define CUSTOM_TRANSLATION 10000

typedef enum {
    TR_NO_PATCH_TITLE,
    TR_NO_PATCH_MESSAGE,
    TR_MISSING_FONTS_TITLE,
    TR_MISSING_FONTS_MESSAGE,
    TR_NO_EDITOR_TITLE,
    TR_NO_EDITOR_MESSAGE,
    TR_INVALID_LANGUAGE_TITLE,
    TR_INVALID_LANGUAGE_MESSAGE,
    TR_BUILD_ALL_TEMPLES,
    TR_BUTTON_OK,
    TR_BUTTON_CANCEL,
    TR_BUTTON_RESET_DEFAULTS,
    TR_BUTTON_CONFIGURE_HOTKEYS,
    TR_CONFIG_ARE_YOU_SURE,
    TR_CONFIG_YOU_WILL_LOSE_YOUR_CONFIGS,
    TR_CONFIG_YOU_WILL_LOSE_YOUR_HOTKEYS,
    TR_CONFIG_TITLE,
    TR_CONFIG_HEADER_GENERAL,
    TR_CONFIG_HEADER_UI_CHANGES,
    TR_CONFIG_HEADER_GAMEPLAY_CHANGES,
    TR_CONFIG_HEADER_CITY_MANAGEMENT_CHANGES,
    TR_CONFIG_LANGUAGE_LABEL,
    TR_CONFIG_LANGUAGE_DEFAULT,
    TR_CONFIG_GAME_SPEED,
    TR_CONFIG_VIDEO,
    TR_CONFIG_FULLSCREEN,
    TR_CONFIG_WINDOWED_RESOLUTION,
    TR_CONFIG_DISPLAY_SCALE,
    TR_CONFIG_CURSOR_SCALE,
    TR_CONFIG_USE_COLOR_CURSORS,
    TR_CONFIG_AUDIO,
    TR_CONFIG_VOLUME,
    TR_CONFIG_ENABLE_AUDIO,
    TR_CONFIG_MUSIC,
    TR_CONFIG_SPEECH,
    TR_CONFIG_EFFECTS,
    TR_CONFIG_CITY_SOUNDS,
    TR_CONFIG_VIDEO_SOUND,
    TR_CONFIG_SCROLL_SPEED,
    TR_CONFIG_SHOW_INTRO_VIDEO,
    TR_CONFIG_SIDEBAR_INFO,
    TR_CONFIG_SMOOTH_SCROLLING,
    TR_CONFIG_DISABLE_MOUSE_EDGE_SCROLLING,
    TR_CONFIG_VISUAL_FEEDBACK_ON_DELETE,
    TR_CONFIG_ALLOW_CYCLING_TEMPLES,
    TR_CONFIG_SHOW_WATER_STRUCTURE_RANGE,
    TR_CONFIG_SHOW_CONSTRUCTION_SIZE,
    TR_CONFIG_HIGHLIGHT_LEGIONS,
    TR_CONFIG_ROTATE_MANUALLY,
    TR_CONFIG_UI_INVERSE_MAP_DRAG,
    TR_CONFIG_UI_MESSAGE_ALERTS,
    TR_CONFIG_UI_SHOW_GRID_DURING_CONSTRUCTION,
    TR_CONFIG_FIX_IMMIGRATION_BUG,
    TR_CONFIG_FIX_100_YEAR_GHOSTS,
    TR_CONFIG_FIX_EDITOR_EVENTS,
    TR_CONFIG_DRAW_WALKER_WAYPOINTS,
    TR_CONFIG_COMPLETE_RATING_COLUMNS,
    TR_CONFIG_GRANDFESTIVAL,
    TR_CONFIG_DIFFICULTY,
    TR_CONFIG_MAX_GRAND_TEMPLES,
    TR_CONFIG_INFINITE,
    TR_CONFIG_GODS_EFFECTS,
    TR_CONFIG_JEALOUS_GODS,
    TR_CONFIG_GLOBAL_LABOUR,
    TR_CONFIG_SCHOOL_WALKERS,
    TR_CONFIG_RETIRE_AT_60,
    TR_CONFIG_FIXED_WORKERS,
    TR_CONFIG_EXTRA_FORTS,
    TR_CONFIG_WOLVES_BLOCK,
    TR_CONFIG_DYNAMIC_GRANARIES,
    TR_CONFIG_MORE_STOCKPILE,
    TR_CONFIG_NO_SUPPLIER_DISTRIBUTION,
    TR_CONFIG_IMMEDIATELY_DELETE_BUILDINGS,
    TR_CONFIG_GETTING_GRANARIES_GO_OFFROAD,
    TR_CONFIG_GRANARIES_GET_DOUBLE,
    TR_CONFIG_ALLOW_EXPORTING_FROM_GRANARIES,
    TR_CONFIG_TOWER_SENTRIES_GO_OFFROAD,
    TR_CONFIG_FARMS_DELIVER_CLOSE,
    TR_CONFIG_DELIVER_ONLY_TO_ACCEPTING_GRANARIES,
    TR_CONFIG_ALL_HOUSES_MERGE,
    TR_CONFIG_WINE_COUNTS_IF_OPEN_TRADE_ROUTE,
    TR_CONFIG_RANDOM_COLLAPSES_TAKE_MONEY,
    TR_CONFIG_MULTIPLE_BARRACKS,
    TR_CONFIG_NOT_ACCEPTING_WAREHOUSES,
    TR_CONFIG_HOUSES_DONT_EXPAND_INTO_GARDENS,
    TR_CONFIG_ROAMERS_DONT_SKIP_CORNERS,
    TR_CONFIG_SHOW_MILITARY_SIDEBAR,
    TR_CONFIG_DISABLE_RIGHT_CLICK_MAP_DRAG,
    TR_CONFIG_SHOW_MAX_POSSIBLE_PROSPERITY,
    TR_HOTKEY_TITLE,
    TR_HOTKEY_LABEL,
    TR_HOTKEY_ALTERNATIVE_LABEL,
    TR_HOTKEY_HEADER_ARROWS,
    TR_HOTKEY_HEADER_GLOBAL,
    TR_HOTKEY_HEADER_CITY,
    TR_HOTKEY_HEADER_ADVISORS,
    TR_HOTKEY_HEADER_OVERLAYS,
    TR_HOTKEY_HEADER_BOOKMARKS,
    TR_HOTKEY_HEADER_EDITOR,
    TR_HOTKEY_HEADER_BUILD,
    TR_HOTKEY_ARROW_UP,
    TR_HOTKEY_ARROW_DOWN,
    TR_HOTKEY_ARROW_LEFT,
    TR_HOTKEY_ARROW_RIGHT,
    TR_HOTKEY_TOGGLE_FULLSCREEN,
    TR_HOTKEY_CENTER_WINDOW,
    TR_HOTKEY_RESIZE_TO_640,
    TR_HOTKEY_RESIZE_TO_800,
    TR_HOTKEY_RESIZE_TO_1024,
    TR_HOTKEY_SAVE_SCREENSHOT,
    TR_HOTKEY_SAVE_CITY_SCREENSHOT,
    TR_HOTKEY_BUILD_CLONE,
    TR_HOTKEY_COPY_SETTINGS,
    TR_HOTKEY_PASTE_SETTINGS,
    TR_HOTKEY_LOAD_FILE,
    TR_HOTKEY_SAVE_FILE,
    TR_HOTKEY_INCREASE_GAME_SPEED,
    TR_HOTKEY_DECREASE_GAME_SPEED,
    TR_HOTKEY_TOGGLE_PAUSE,
    TR_HOTKEY_CYCLE_LEGION,
    TR_HOTKEY_ROTATE_MAP_LEFT,
    TR_HOTKEY_ROTATE_MAP_RIGHT,
    TR_HOTKEY_SHOW_ADVISOR_LABOR,
    TR_HOTKEY_SHOW_ADVISOR_MILITARY,
    TR_HOTKEY_SHOW_ADVISOR_IMPERIAL,
    TR_HOTKEY_SHOW_ADVISOR_RATINGS,
    TR_HOTKEY_SHOW_ADVISOR_TRADE,
    TR_HOTKEY_SHOW_ADVISOR_POPULATION,
    TR_HOTKEY_SHOW_ADVISOR_HEALTH,
    TR_HOTKEY_SHOW_ADVISOR_EDUCATION,
    TR_HOTKEY_SHOW_ADVISOR_ENTERTAINMENT,
    TR_HOTKEY_SHOW_ADVISOR_RELIGION,
    TR_HOTKEY_SHOW_ADVISOR_FINANCIAL,
    TR_HOTKEY_SHOW_ADVISOR_CHIEF,
    TR_HOTKEY_SHOW_ADVISOR_HOUSING,
    TR_HOTKEY_TOGGLE_OVERLAY,
    TR_HOTKEY_SHOW_OVERLAY_RELATIVE,
    TR_HOTKEY_SHOW_OVERLAY_WATER,
    TR_HOTKEY_SHOW_OVERLAY_FIRE,
    TR_HOTKEY_SHOW_OVERLAY_DAMAGE,
    TR_HOTKEY_SHOW_OVERLAY_CRIME,
    TR_HOTKEY_SHOW_OVERLAY_PROBLEMS,
    TR_HOTKEY_ROTATE_BUILDING,
    TR_HOTKEY_ROTATE_BUILDING_BACK,
    TR_HOTKEY_GO_TO_BOOKMARK_1,
    TR_HOTKEY_GO_TO_BOOKMARK_2,
    TR_HOTKEY_GO_TO_BOOKMARK_3,
    TR_HOTKEY_GO_TO_BOOKMARK_4,
    TR_HOTKEY_SET_BOOKMARK_1,
    TR_HOTKEY_SET_BOOKMARK_2,
    TR_HOTKEY_SET_BOOKMARK_3,
    TR_HOTKEY_SET_BOOKMARK_4,
    TR_HOTKEY_EDITOR_TOGGLE_BATTLE_INFO,
    TR_HOTKEY_EDIT_TITLE,
    TR_BUILDING_ARCHITECT_GUILD,
    TR_BUILDING_ARCHITECT_GUILD_DESC,
    TR_BUILDING_GRAND_TEMPLE_ADD_MODULE,
    TR_BUILDING_GRAND_TEMPLE_CERES,
    TR_BUILDING_GRAND_TEMPLE_NEPTUNE,
    TR_BUILDING_GRAND_TEMPLE_MERCURY,
    TR_BUILDING_GRAND_TEMPLE_MARS,
    TR_BUILDING_GRAND_TEMPLE_VENUS,
    TR_BUILDING_PANTHEON,
    TR_BUILDING_GRAND_TEMPLE_CERES_DESC,
    TR_BUILDING_GRAND_TEMPLE_NEPTUNE_DESC,
    TR_BUILDING_GRAND_TEMPLE_MERCURY_DESC,
    TR_BUILDING_GRAND_TEMPLE_MARS_DESC,
    TR_BUILDING_GRAND_TEMPLE_VENUS_DESC,
    TR_BUILDING_PANTHEON_DESC,
    TR_BUILDING_GRAND_TEMPLE_CERES_BONUS_DESC,
    TR_BUILDING_GRAND_TEMPLE_NEPTUNE_BONUS_DESC,
    TR_BUILDING_GRAND_TEMPLE_MERCURY_BONUS_DESC,
    TR_BUILDING_GRAND_TEMPLE_MARS_BONUS_DESC,
    TR_BUILDING_GRAND_TEMPLE_VENUS_BONUS_DESC,
    TR_BUILDING_PANTHEON_BONUS_DESC,
    TR_BUILDING_GRAND_TEMPLE_CERES_MODULE_1_DESC,
    TR_BUILDING_GRAND_TEMPLE_NEPTUNE_MODULE_1_DESC,
    TR_BUILDING_GRAND_TEMPLE_MERCURY_MODULE_1_DESC,
    TR_BUILDING_GRAND_TEMPLE_MARS_MODULE_1_DESC,
    TR_BUILDING_GRAND_TEMPLE_VENUS_MODULE_1_DESC,
    TR_BUILDING_GRAND_TEMPLE_CERES_MODULE_2_DESC,
    TR_BUILDING_GRAND_TEMPLE_NEPTUNE_MODULE_2_DESC,
    TR_BUILDING_GRAND_TEMPLE_MERCURY_MODULE_2_DESC,
    TR_BUILDING_GRAND_TEMPLE_MARS_MODULE_2_DESC,
    TR_BUILDING_GRAND_TEMPLE_VENUS_MODULE_2_DESC,
    TR_BUILDING_PANTHEON_MODULE_1_DESC,
    TR_BUILDING_PANTHEON_MODULE_2_DESC,
    TR_BUILDING_GRAND_TEMPLE_CERES_DESC_MODULE_1,
    TR_BUILDING_GRAND_TEMPLE_CERES_DESC_MODULE_2,
    TR_BUILDING_GRAND_TEMPLE_NEPTUNE_DESC_MODULE_1,
    TR_BUILDING_GRAND_TEMPLE_NEPTUNE_DESC_MODULE_2,
    TR_BUILDING_GRAND_TEMPLE_MERCURY_DESC_MODULE_1,
    TR_BUILDING_GRAND_TEMPLE_MERCURY_DESC_MODULE_2,
    TR_BUILDING_GRAND_TEMPLE_MARS_DESC_MODULE_1,
    TR_BUILDING_GRAND_TEMPLE_MARS_DESC_MODULE_2,
    TR_BUILDING_GRAND_TEMPLE_VENUS_DESC_MODULE_1,
    TR_BUILDING_GRAND_TEMPLE_VENUS_DESC_MODULE_2,
    TR_BUILDING_PANTHEON_DESC_MODULE_1,
    TR_BUILDING_PANTHEON_DESC_MODULE_2,
    TR_BUILDING_GRAND_TEMPLE_MENU,
    TR_BUILDING_ROADBLOCK,
    TR_BUILDING_ROADBLOCK_DESC,
    TR_BUILDING_WORK_CAMP,
    TR_BUILDING_WORK_CAMP_DESC,
    TR_HEADER_HOUSING,
    TR_ADVISOR_HOUSING_ROOM,
    TR_ADVISOR_HOUSING_NO_ROOM,
    TR_ADVISOR_RESIDENCES_DEMANDING_POTTERY,
    TR_ADVISOR_RESIDENCES_DEMANDING_FURNITURE,
    TR_ADVISOR_RESIDENCES_DEMANDING_OIL,
    TR_ADVISOR_RESIDENCES_DEMANDING_WINE,
    TR_ADVISOR_TOTAL_NUM_HOUSES,
    TR_ADVISOR_AVAILABLE_HOUSING_CAPACITY,
    TR_ADVISOR_TOTAL_HOUSING_CAPACITY,
    TR_ADVISOR_ADVISOR_HEADER_HOUSING,
    TR_ADVISOR_BUTTON_GRAPHS,
    TR_ADVISOR_HOUSING_PROSPERITY_RATING,
    TR_ADVISOR_PERCENTAGE_IN_VILLAS_PALACES,
    TR_ADVISOR_PERCENTAGE_IN_TENTS_SHACKS,
    TR_ADVISOR_AVERAGE_TAX,
    TR_ADVISOR_AVERAGE_AGE,
    TR_ADVISOR_PERCENT_IN_WORKFORCE,
    TR_ADVISOR_BIRTHS_LAST_YEAR,
    TR_ADVISOR_DEATHS_LAST_YEAR,
    TR_ADVISOR_TOTAL_POPULATION,
    TR_ADVISOR_IN_STORAGE,
    TR_ADVISOR_FROM_GRANARIES,
    TR_ADVISOR_DISPATCHING_FOOD_FROM_GRANARIES_TITLE,
    TR_ADVISOR_DISPATCHING_FOOD_FROM_GRANARIES_TEXT,
    TR_ADVISOR_KEEP_STOCKPILING,
    TR_ADVISOR_MAX_ATTAINABLE_PROSPERITY_REACHED,
    TR_ADVISOR_MAX_ATTAINABLE_PROSPERITY_IS,
    TR_ADVISOR_POPULATION_AGE,
    TR_ADVISOR_POPULATION_RESIDENTS,
    TR_ADVISOR_POPULATION_DWELLERS,
    TR_REQUIRED_RESOURCES,
    TR_BUILDING_GRAND_TEMPLE_CONSTRUCTION_DESC,
    TR_CONSTRUCTION_PHASE,
    TR_ADD_MODULE,
    TR_BUILDING_TEMPLE_MODULE_CONSTRUCTED,
    TR_BUILDING_CERES_TEMPLE_QUOTE,
    TR_BUILDING_NEPTUNE_TEMPLE_QUOTE,
    TR_BUILDING_MERCURY_TEMPLE_QUOTE,
    TR_BUILDING_MARS_TEMPLE_QUOTE,
    TR_BUILDING_VENUS_TEMPLE_QUOTE,
    TR_BUILDING_PANTHEON_QUOTE,
    TR_BUILDING_GRAND_TEMPLE_PHASE_1,
    TR_BUILDING_GRAND_TEMPLE_PHASE_2,
    TR_BUILDING_GRAND_TEMPLE_PHASE_3,
    TR_BUILDING_GRAND_TEMPLE_PHASE_4,
    TR_BUILDING_GRAND_TEMPLE_PHASE_5,
    TR_BUILDING_GRAND_TEMPLE_PHASE_1_TEXT,
    TR_BUILDING_GRAND_TEMPLE_PHASE_2_TEXT,
    TR_BUILDING_GRAND_TEMPLE_PHASE_3_TEXT,
    TR_BUILDING_GRAND_TEMPLE_PHASE_4_TEXT,
    TR_BUILDING_GRAND_TEMPLE_PHASE_5_TEXT,
    TR_BUILDING_MENU_TREES,
    TR_BUILDING_MENU_PATHS,
    TR_BUILDING_MENU_PARKS,
    TR_BUILDING_SMALL_POND,
    TR_BUILDING_LARGE_POND,
    TR_BUILDING_PINE_TREE,
    TR_BUILDING_FIR_TREE,
    TR_BUILDING_OAK_TREE,
    TR_BUILDING_ELM_TREE,
    TR_BUILDING_FIG_TREE,
    TR_BUILDING_PLUM_TREE,
    TR_BUILDING_PALM_TREE,
    TR_BUILDING_DATE_TREE,
    TR_BUILDING_PINE_PATH,
    TR_BUILDING_FIR_PATH,
    TR_BUILDING_OAK_PATH,
    TR_BUILDING_ELM_PATH,
    TR_BUILDING_FIG_PATH,
    TR_BUILDING_PLUM_PATH,
    TR_BUILDING_PALM_PATH,
    TR_BUILDING_DATE_PATH,
    TR_BUILDING_BLUE_PAVILION,
    TR_BUILDING_RED_PAVILION,
    TR_BUILDING_ORANGE_PAVILION,
    TR_BUILDING_YELLOW_PAVILION,
    TR_BUILDING_GREEN_PAVILION,
    TR_BUILDING_SMALL_STATUE_ALT,
    TR_BUILDING_SMALL_STATUE_ALT_B,
    TR_BUILDING_OBELISK,
    TR_BUILDING_POND_DESC,
    TR_BUILDING_WINDOW_POND,
    TR_BUILDING_OBELISK_DESC,
    TR_ADVISOR_FINANCE_LEVIES,
    TR_CONFIRM_DELETE_MONUMENT,
    TR_SELECT_EPITHET_PROMPT_HEADER,
    TR_SELECT_EPITHET_PROMPT_TEXT,
    TR_BUILDING_INFO_MONTHLY_LEVY,
    TR_BUILDING_MESS_HALL,
    TR_BUILDING_MESS_HALL_DESC,
    TR_BUILDING_MESS_HALL_FULFILLMENT,
    TR_BUILDING_MESS_HALL_TROOP_HUNGER,
    TR_BUILDING_MESS_HALL_TROOP_HUNGER_1,
    TR_BUILDING_MESS_HALL_TROOP_HUNGER_2,
    TR_BUILDING_MESS_HALL_TROOP_HUNGER_3,
    TR_BUILDING_MESS_HALL_TROOP_HUNGER_4,
    TR_BUILDING_MESS_HALL_TROOP_HUNGER_5,
    TR_BUILDING_MESS_HALL_FOOD_TYPES_BONUS_1,
    TR_BUILDING_MESS_HALL_FOOD_TYPES_BONUS_2,
    TR_BUILDING_MESS_HALL_NO_SOLDIERS,
    TR_BUILDING_MESS_HALL_MONTHS_FOOD_STORED,
    TR_MESS_HALL_SPECIAL_ORDERS_HEADER,
    TR_BUILDING_BARRACKS_FOOD_WARNING,
    TR_BUILDING_BARRACKS_FOOD_WARNING_2,
    TR_BUILDING_LEGION_FOOD_WARNING_1,
    TR_BUILDING_LEGION_FOOD_WARNING_2,
    TR_BUILDING_LEGION_STARVING,
    TR_ADVISOR_TRADE_MAX,
    TR_ADVISOR_TRADE_NO_LIMIT,
    TR_ADVISOR_TRADE_IMPORTABLE,
    TR_ADVISOR_TRADE_EXPORTABLE,
    TR_ADVISOR_TRADE_IMPORTABLE_EXPORTABLE,
    TR_ADVISOR_TRADE_NO_BUYERS,
    TR_ADVISOR_TRADE_NO_SELLERS,
    TR_ADVISOR_TRADE_NOT_IMPORTING,
    TR_ADVISOR_TRADE_NOT_EXPORTING,
    TR_ADVISOR_OPEN_TO_IMPORT,
    TR_ADVISOR_OPEN_TO_EXPORT,
    TR_ADVISOR_LEGION_FOOD_SATISFIED,
    TR_ADVISOR_LEGION_FOOD_NEEDED,
    TR_ADVISOR_LEGION_FOOD_CRITICAL,
    TR_ADVISOR_LEGION_MONTHS_FOOD_STORED,
    TR_CITY_MESSAGE_TITLE_MESS_HALL_NEEDS_FOOD,
    TR_CITY_MESSAGE_TEXT_MESS_HALL_NEEDS_FOOD,
    TR_CITY_MESSAGE_TEXT_MESS_HALL_MISSING,
    TR_MARKET_SPECIAL_ORDERS_HEADER,
    TR_DOCK_SPECIAL_ORDERS_HEADER,
    TR_TEMPLE_SPECIAL_ORDERS_HEADER,
    TR_TAVERN_SPECIAL_ORDERS_HEADER,
    TR_WARNING_NO_MESS_HALL,
    TR_WARNING_MAX_GRAND_TEMPLES,
    TR_CITY_MESSAGE_TITLE_GRAND_TEMPLE_COMPLETE,
    TR_CITY_MESSAGE_TEXT_GRAND_TEMPLE_COMPLETE,
    TR_CITY_MESSAGE_TITLE_MERCURY_BLESSING,
    TR_CITY_MESSAGE_TEXT_MERCURY_BLESSING,
    TR_FIGURE_TYPE_WORK_CAMP_WORKER,
    TR_FIGURE_TYPE_WORK_CAMP_SLAVE,
    TR_FIGURE_TYPE_WORK_CAMP_ARCHITECT,
    TR_FIGURE_TYPE_MESS_HALL_SUPPLIER,
    TR_FIGURE_TYPE_MESS_HALL_COLLECTOR,
    TR_BUILDING_CERES_TEMPLE_MODULE_DESC,
    TR_BUILDING_VENUS_TEMPLE_MODULE_DESC,
    TR_BUILDING_MARS_TEMPLE_MODULE_DESC,
    TR_BUILDING_SMALL_TEMPLE_CERES_NAME,
    TR_BUILDING_SMALL_TEMPLE_NEPTUNE_NAME,
    TR_BUILDING_SMALL_TEMPLE_MERCURY_NAME,
    TR_BUILDING_SMALL_TEMPLE_MARS_NAME,
    TR_BUILDING_SMALL_TEMPLE_VENUS_NAME,
    TR_FIGURE_TYPE_PRIEST_SUPPLIER,
    TR_BUILDING_DOCK_CITIES_CONFIG_DESC,
    TR_BUILDING_DOCK_CITIES_NO_ROUTES,
    TR_PHRASE_FIGURE_MISSIONARY_EXACT_4,
    TR_CITY_MESSAGE_TITLE_PANTHEON_FESTIVAL,
    TR_CITY_MESSAGE_TEXT_PANTHEON_FESTIVAL_CERES,
    TR_CITY_MESSAGE_TEXT_PANTHEON_FESTIVAL_NEPTUNE,
    TR_CITY_MESSAGE_TEXT_PANTHEON_FESTIVAL_MERCURY,
    TR_CITY_MESSAGE_TEXT_PANTHEON_FESTIVAL_MARS,
    TR_CITY_MESSAGE_TEXT_PANTHEON_FESTIVAL_VENUS,
    TR_TOOLTIP_BUTTON_DELETE_READ_MESSAGES,
    TR_TOOLTIP_BUTTON_MOTHBALL_ON,
    TR_TOOLTIP_BUTTON_MOTHBALL_OFF,
    TR_TOOLTIP_BUTTON_ACCEPT_MARKET_LADIES,
    TR_TOOLTIP_BUTTON_ACCEPT_TRADE_CARAVAN,
    TR_TOOLTIP_BUTTON_ACCEPT_TRADE_SHIPS,
    TR_BUILDING_LIGHTHOUSE,
    TR_BUILDING_CARAVANSERAI,
    TR_BUILDING_CARAVANSERAI_DESC,
    TR_CARAVANSERAI_SPECIAL_ORDERS_HEADER,
    TR_BUILDING_CARAVANSERAI_PHASE_1,
    TR_BUILDING_CARAVANSERAI_PHASE_1_TEXT,
    TR_FIGURE_TYPE_CARAVANSERAI_SUPPLIER,
    TR_FIGURE_TYPE_CARAVANSERAI_COLLECTOR,
    TR_BUILDING_CARAVANSERAI_POLICY_TITLE,
    TR_BUILDING_CARAVANSERAI_NO_POLICY,
    TR_BUILDING_CARAVANSERAI_POLICY_TEXT,
    TR_BUILDING_CARAVANSERAI_POLICY_1_TITLE,
    TR_BUILDING_CARAVANSERAI_POLICY_1,
    TR_BUILDING_CARAVANSERAI_POLICY_2_TITLE,
    TR_BUILDING_CARAVANSERAI_POLICY_2,
    TR_BUILDING_CARAVANSERAI_POLICY_3_TITLE,
    TR_BUILDING_CARAVANSERAI_POLICY_3,
    TR_BUILDING_LIGHTHOUSE_PHASE_1,
    TR_BUILDING_LIGHTHOUSE_PHASE_2,
    TR_BUILDING_LIGHTHOUSE_PHASE_3,
    TR_BUILDING_LIGHTHOUSE_PHASE_4,
    TR_BUILDING_LIGHTHOUSE_PHASE_1_TEXT,
    TR_BUILDING_LIGHTHOUSE_PHASE_2_TEXT,
    TR_BUILDING_LIGHTHOUSE_PHASE_3_TEXT,
    TR_BUILDING_LIGHTHOUSE_PHASE_4_TEXT,
    TR_BUILDING_LIGHTHOUSE_CONSTRUCTION_DESC,
    TR_BUILDING_LIGHTHOUSE_BONUS_DESC,
    TR_BUILDING_LIGHTHOUSE_POLICY_TITLE,
    TR_BUILDING_LIGHTHOUSE_NO_POLICY,
    TR_BUILDING_LIGHTHOUSE_POLICY_TEXT,
    TR_BUILDING_LIGHTHOUSE_POLICY_1_TITLE,
    TR_BUILDING_LIGHTHOUSE_POLICY_1,
    TR_BUILDING_LIGHTHOUSE_POLICY_2_TITLE,
    TR_BUILDING_LIGHTHOUSE_POLICY_2,
    TR_BUILDING_LIGHTHOUSE_POLICY_3_TITLE,
    TR_BUILDING_LIGHTHOUSE_POLICY_3,
    TR_EDITOR_ALLOWED_BUILDINGS_MONUMENTS,
    TR_CITY_MESSAGE_TEXT_LIGHTHOUSE_COMPLETE,
    TR_CITY_MESSAGE_TEXT_PANTHEON_COMPLETE,
    TR_CITY_MESSAGE_TITLE_MONUMENT_COMPLETE,
    TR_CITY_MESSAGE_TITLE_NEPTUNE_BLESSING,
    TR_CITY_MESSAGE_TEXT_NEPTUNE_BLESSING,
    TR_CITY_MESSAGE_TITLE_VENUS_BLESSING,
    TR_CITY_MESSAGE_TEXT_VENUS_BLESSING,
    TR_BUILDING_MENU_STATUES,
    TR_BUILDING_MENU_GOV_RES,
    TR_OVERLAY_ROADS,
    TR_NO_EXTRA_ASSETS_TITLE,
    TR_NO_EXTRA_ASSETS_MESSAGE,
    TR_WARNING_WATER_NEEDED_FOR_LIGHTHOUSE,
    TR_TOOLTIP_OVERLAY_PANTHEON_ACCESS,
    TR_BUILDING_LEGION_FOOD_BONUS,
    TR_BUILDING_LEGION_FOOD_STATUS,
    TR_TOOLTIP_BUTTON_ACCEPT_QUARTERMASTER,
    TR_WARNING_RESOURCES_NOT_AVAILABLE,
    TR_CONFIG_GP_CH_MONUMENTS_BOOST_CULTURE_RATING,
    TR_CONFIG_GP_CH_DISABLE_INFINITE_WOLVES_SPAWNING,
    TR_BUTTON_BACK_TO_MAIN_MENU,
    TR_LABEL_PAUSE_MENU,
    TR_OVERLAY_LEVY,
    TR_TOOLTIP_OVERLAY_LEVY,
    TR_MAP_EDITOR_OPTIONS,
    TR_BUILDING_TAVERN,
    TR_BUILDING_GRAND_GARDEN,
    TR_BUILDING_TAVERN_DESC_1,
    TR_BUILDING_TAVERN_DESC_2,
    TR_BUILDING_TAVERN_DESC_3,
    TR_BUILDING_TAVERN_DESC_4,
    TR_FIGURE_TYPE_BARKEEP,
    TR_FIGURE_TYPE_BARKEEP_SUPPLIER,
    TR_OVERLAY_TAVERN,
    TR_TOOLTIP_OVERLAY_TAVERN_1,
    TR_TOOLTIP_OVERLAY_TAVERN_2,
    TR_TOOLTIP_OVERLAY_TAVERN_3,
    TR_TOOLTIP_OVERLAY_TAVERN_4,
    TR_TOOLTIP_OVERLAY_TAVERN_5,
    TR_TOOLTIP_OVERLAY_TAVERN_6,
    TR_BUILDING_WINDOW_HOUSE_SENTIMENT_1,
    TR_BUILDING_WINDOW_HOUSE_SENTIMENT_2,
    TR_BUILDING_WINDOW_HOUSE_SENTIMENT_3,
    TR_BUILDING_WINDOW_HOUSE_SENTIMENT_4,
    TR_BUILDING_WINDOW_HOUSE_SENTIMENT_5,
    TR_BUILDING_WINDOW_HOUSE_SENTIMENT_6,
    TR_BUILDING_WINDOW_HOUSE_SENTIMENT_7,
    TR_BUILDING_WINDOW_HOUSE_SENTIMENT_8,
    TR_BUILDING_WINDOW_HOUSE_SENTIMENT_9,
    TR_BUILDING_WINDOW_HOUSE_SENTIMENT_10,
    TR_BUILDING_WINDOW_HOUSE_SENTIMENT_11,
    TR_BUILDING_WINDOW_HOUSE_SENTIMENT_12,
    TR_BUILDING_WINDOW_HOUSE_UPSET_HIGH_TAXES,
    TR_BUILDING_WINDOW_HOUSE_UPSET_LOW_WAGES,
    TR_BUILDING_WINDOW_HOUSE_UPSET_UNEMPLOYMENT,
    TR_BUILDING_WINDOW_HOUSE_UPSET_SQUALOR,
    TR_BUILDING_WINDOW_HOUSE_SUGGEST_ENTERTAINMENT,
    TR_BUILDING_WINDOW_HOUSE_SUGGEST_FOOD,
    TR_BUILDING_WINDOW_HOUSE_SUGGEST_DESIRABILITY,
    TR_BUILDING_WINDOW_HOUSE_RECENT_EVENT_POSITIVE,
    TR_BUILDING_WINDOW_HOUSE_RECENT_EVENT_NEGATIVE,
    TR_BUILDING_WINDOW_INDUSTRY_EFFICIENCY,
    TR_BUILDING_WINDOW_INDUSTRY_EFFICIENCY_TOOLTIP,
    TR_BUILDING_WINDOW_INDUSTRY_LOW_EFFICIENCY_RAW_MATERIALS,
    TR_BUILDING_WINDOW_INDUSTRY_LOW_EFFICIENCY_WORKSHOPS,
    TR_BUILDING_WINDOW_INDUSTRY_WHARF_AVERAGE_CATCH,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_TAVERN_COVERAGE,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_GAMES_HEADER,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_GAMES_DESC,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_GAMES_BUTTON,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_GAMES_PREPARING,
    TR_SELECT_GAMES_HEADER,
    TR_SELECT_GAMES_TEXT,
    TR_BUILDING_ARENA,
    TR_BUILDING_HORSE_STATUE,
    TR_BUILDING_DOLPHIN_FOUNTAIN,
    TR_BUILDING_HEDGE_DARK,
    TR_BUILDING_HEDGE_LIGHT,
    TR_BUILDING_GARDEN_WALL,
    TR_BUILDING_LEGION_STATUE,
    TR_BUILDING_DECORATIVE_COLUMN,
    TR_BUILDING_COLOSSEUM_PHASE_1,
    TR_BUILDING_COLOSSEUM_PHASE_2,
    TR_BUILDING_COLOSSEUM_PHASE_3,
    TR_BUILDING_COLOSSEUM_PHASE_4,
    TR_BUILDING_COLOSSEUM_PHASE_1_TEXT,
    TR_BUILDING_COLOSSEUM_PHASE_2_TEXT,
    TR_BUILDING_COLOSSEUM_PHASE_3_TEXT,
    TR_BUILDING_COLOSSEUM_PHASE_4_TEXT,
    TR_BUILDING_HIPPODROME_PHASE_1,
    TR_BUILDING_HIPPODROME_PHASE_2,
    TR_BUILDING_HIPPODROME_PHASE_3,
    TR_BUILDING_HIPPODROME_PHASE_4,
    TR_BUILDING_HIPPODROME_PHASE_1_TEXT,
    TR_BUILDING_HIPPODROME_PHASE_2_TEXT,
    TR_BUILDING_HIPPODROME_PHASE_3_TEXT,
    TR_BUILDING_HIPPODROME_PHASE_4_TEXT,
    TR_BUILDING_MONUMENT_CONSTRUCTION_DESC,
    TR_BUILDING_MONUMENT_CONSTRUCTION_HALTED,
    TR_BUILDING_MONUMENT_CONSTRUCTION_ARCHITECT_NEEDED,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_ARENA_COVERAGE,
    TR_BUILDING_INFO_TOURISM,
    TR_CITY_MESSAGE_TEXT_COLOSSEUM_COMPLETE,
    TR_CITY_MESSAGE_TEXT_HIPPODROME_COMPLETE,
    TR_CITY_MESSAGE_TITLE_COLOSSEUM_WORKING,
    TR_CITY_MESSAGE_TITLE_HIPPODROME_WORKING,
    TR_CITY_MESSAGE_TEXT_COLOSSEUM_WORKING,
    TR_CITY_MESSAGE_TEXT_HIPPODROME_WORKING,
    TR_WINDOW_GAMES_OPTION_1,
    TR_WINDOW_GAMES_OPTION_2,
    TR_WINDOW_GAMES_OPTION_3,
    TR_WINDOW_GAMES_OPTION_4,
    TR_WINDOW_GAMES_OPTION_5,
    TR_WINDOW_GAMES_OPTION_1_DESC,
    TR_WINDOW_GAMES_OPTION_2_DESC,
    TR_WINDOW_GAMES_OPTION_3_DESC,
    TR_WINDOW_GAMES_OPTION_4_DESC,
    TR_WINDOW_GAMES_OPTION_5_DESC,
    TR_WINDOW_GAMES_COST,
    TR_WINDOW_GAMES_PERSONAL_FUNDS,
    TR_WINDOW_GAMES_NOT_ENOUGH_FUNDS,
    TR_WINDOW_GAMES_NOT_ENOUGH_RESOURCES,
    TR_WINDOW_GAMES_NO_WATER_ACCESS,
    TR_WINDOW_GAMES_NO_VENUE,
    TR_BUILDING_SMALL_TEMPLE_PHASE_1,
    TR_BUILDING_SMALL_TEMPLE_PHASE_1_TEXT,
    TR_BUILDING_SMALL_TEMPLE_CONSTRUCTION_DESC,
    TR_CITY_MESSAGE_TEXT_NAVAL_GAMES_PLANNING,
    TR_CITY_MESSAGE_TEXT_NAVAL_GAMES_STARTING,
    TR_CITY_MESSAGE_TEXT_NAVAL_GAMES_ENDING,
    TR_CITY_MESSAGE_TEXT_ANIMAL_GAMES_PLANNING,
    TR_CITY_MESSAGE_TEXT_ANIMAL_GAMES_STARTING,
    TR_CITY_MESSAGE_TEXT_ANIMAL_GAMES_ENDING,
    TR_CITY_MESSAGE_TEXT_KALENDS_GAMES_PLANNING,
    TR_CITY_MESSAGE_TEXT_KALENDS_GAMES_STARTING,
    TR_CITY_MESSAGE_TEXT_KALENDS_GAMES_ENDING,
    TR_CITY_MESSAGE_TEXT_OLYMPIC_GAMES_PLANNING,
    TR_CITY_MESSAGE_TEXT_OLYMPIC_GAMES_STARTING,
    TR_CITY_MESSAGE_TEXT_OLYMPIC_GAMES_ENDING,
    TR_CITY_MESSAGE_TEXT_IMPERIAL_GAMES_PLANNING,
    TR_CITY_MESSAGE_TEXT_IMPERIAL_GAMES_STARTING,
    TR_CITY_MESSAGE_TEXT_IMPERIAL_GAMES_ENDING,
    TR_CITY_MESSAGE_TITLE_GREAT_GAMES,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_GAMES_COOLDOWN,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_PREPARING_NG,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_UNDERWAY_NG,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_PREPARING_AG,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_UNDERWAY_AG,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_PREPARING_KG,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_UNDERWAY_KG,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_PREPARING_OG,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_UNDERWAY_OG,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_PREPARING_IG,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_UNDERWAY_IG,
    TR_WINDOW_BUILDING_GAMES_REMAINING_DURATION,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_GAMES_COOLDOWN_TEXT,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_GAMES_UNDERWAY,
    TR_WINDOW_BUILDING_ARENA_CLOSED,
    TR_WINDOW_BUILDING_ARENA_NO_SHOWS,
    TR_WINDOW_BUILDING_ARENA_BOTH_SHOWS,
    TR_WINDOW_BUILDING_ARENA_NEEDS_LIONS,
    TR_WINDOW_BUILDING_ARENA_NEEDS_GLADIATORS,
    TR_BUILDING_MARS_TEMPLE_MODULE_DESC_NO_MESS,
    TR_OVERLAY_ARENA_COL,
    TR_TOOLTIP_OVERLAY_ARENA_COL_1,
    TR_TOOLTIP_OVERLAY_ARENA_COL_2,
    TR_TOOLTIP_OVERLAY_ARENA_COL_3,
    TR_TOOLTIP_OVERLAY_ARENA_COL_4,
    TR_TOOLTIP_OVERLAY_ARENA_COL_5,
    TR_TOOLTIP_OVERLAY_ARENA_COL_6,
    TR_TOOLTIP_OVERLAY_PROBLEMS_STRIKE,
    TR_TOOLTIP_OVERLAY_PROBLEMS_NO_WATER_ACCESS,
    TR_TOOLTIP_OVERLAY_PROBLEMS_CARTPUSHER,
    TR_TOOLTIP_OVERLAY_PROBLEMS_NO_RESOURCES,
    TR_TOOLTIP_OVERLAY_PROBLEMS_MOTHBALLED,
    TR_WINDOW_BUILDING_TOURISM_DISABLED,
    TR_WINDOW_BUILDING_TOURISM_ANNUAL,
    TR_WINDOW_BUILDING_WHARF_MOTHBALLED,
    TR_WINDOW_ADVISOR_FINANCE_INTEREST_TRIBUTE,
    TR_WINDOW_ADVISOR_TOURISM,
    TR_WINDOW_FIGURE_TOURIST,
    TR_FIGURE_TYPE_TOURIST,
    TR_SAVEGAME_LARGER_VERSION_TITLE,
    TR_SAVEGAME_LARGER_VERSION_MESSAGE,
    TR_SAVEGAME_NOT_ABLE_TO_SAVE_TITLE,
    TR_SAVEGAME_NOT_ABLE_TO_SAVE_MESSAGE,
    TR_BUILDING_COLONNADE,
    TR_BUILDING_LARARIUM,
    TR_WINDOW_BUILDING_LARARIUM_DESC,
    TR_BUILDING_WATCHTOWER,
    TR_BUILDING_WATCHTOWER_DESC,
    TR_BUILDING_WATCHTOWER_DESC_NO_SOLDIERS,
    TR_BUILDING_NYMPHAEUM,
    TR_BUILDING_NYMPHAEUM_DESC,
    TR_BUILDING_SMALL_MAUSOLEUM,
    TR_BUILDING_SMALL_MAUSOLEUM_DESC,
    TR_BUILDING_LARGE_MAUSOLEUM,
    TR_BUILDING_LARGE_MAUSOLEUM_DESC,
    TR_FIGURE_TYPE_WATCHMAN,
    TR_TOOLTIP_BUTTON_ROADBLOCK_PERMISSION_MAINTENANCE,
    TR_TOOLTIP_BUTTON_ROADBLOCK_PERMISSION_PRIEST,
    TR_TOOLTIP_BUTTON_ROADBLOCK_PERMISSION_MARKET,
    TR_TOOLTIP_BUTTON_ROADBLOCK_PERMISSION_ENTERTAINER,
    TR_TOOLTIP_BUTTON_ROADBLOCK_PERMISSION_EDUCATION,
    TR_TOOLTIP_BUTTON_ROADBLOCK_PERMISSION_MEDICINE,
    TR_TOOLTIP_BUTTON_ROADBLOCK_PERMISSION_TAX_COLLECTOR,
    TR_TOOLTIP_BUTTON_ROADBLOCK_PERMISSION_LABOR_SEEKER,
    TR_TOOLTIP_BUTTON_ROADBLOCK_PERMISSION_MISSIONARY,
    TR_TOOLTIP_BUTTON_ROADBLOCK_PERMISSION_WATCHMAN,
    TR_HOTKEY_DUPLICATE_TITLE,
    TR_HOTKEY_DUPLICATE_MESSAGE,
    TR_BUILDING_GARDEN_PATH,
    TR_BUTTON_GO_TO_SITE,
    TR_BUTTON_HALT_MONUMENT_CONSTRUCTION,
    TR_BUTTON_RESUME_MONUMENT_CONSTRUCTION,
    TR_RESOURCE_FISH,
    TR_WARNING_VARIANT_TOGGLE,
    TR_BUILDING_SCHOOL_UPGRADE_DESC,
    TR_BUILDING_THEATRE_UPGRADE_DESC,
    TR_BUILDING_LIBRARY_UPGRADE_DESC,
    TR_WINDOW_BUILDING_INFO_WARNING_NO_MONUMENT_ROAD_ACCESS,
    TR_WINDOW_BUILDING_WORKSHOP_STRIKING,
    TR_CITY_WARNING_SECESSION,
    TR_CITY_WARNING_WAREHOUSE_BREAKIN,
    TR_CITY_WARNING_GRANARY_BREAKIN,
    TR_CITY_WARNING_MARKET_BREAKIN,
    TR_CITY_WARNING_THEFT,
    TR_CITY_MESSAGE_TITLE_LOOTING,
    TR_CITY_MESSAGE_TEXT_LOOTING,
    TR_SIDEBAR_EXTRA_INVASIONS,
    TR_SIDEBAR_EXTRA_INVASION_UNDERWAY,
    TR_SIDEBAR_EXTRA_NO_INVASIONS,
    TR_SIDEBAR_EXTRA_INVASION_IMMINENT,
    TR_SIDEBAR_EXTRA_ENEMIES_CLOSING,
    TR_SIDEBAR_EXTRA_ENEMIES_DISTANT,
    TR_SIDEBAR_EXTRA_GODS,
    TR_SIDEBAR_EXTRA_REQUESTS_VIEW_ALL,
    TR_SIDEBAR_EXTRA_REQUESTS_SMALL_FORCE,
    TR_SIDEBAR_EXTRA_REQUESTS_AVERAGE_FORCE,
    TR_SIDEBAR_EXTRA_REQUESTS_LARGE_FORCE,
    TR_SIDEBAR_EXTRA_REQUESTS_SEND,
    TR_SIDEBAR_EXTRA_REQUESTS_STOCK,
    TR_SIDEBAR_EXTRA_REQUESTS_UNSTOCK,
    TR_TOOLTIP_ADVISOR_HOUSING_GRAPH_BUTTON,
    TR_TOOLTIP_ADVISOR_POPULATION_HOUSING_BUTTON,
    TR_RETURN_ALL_TO_FORT,
    TR_TOOLTIP_ADVISOR_ENTERTAINMENT_GAMES_BUTTON,
    TR_WINDOW_BUILDING_GOVERNMENT_LARGE_STATUE_WATER_WARNING,
    TR_OPTION_MENU_APPLY,
    TR_OPTION_MENU_COST,
    TR_FIGURE_TYPE_LOOTER,
    TR_FIGURE_TYPE_ROBBER,
    TR_OVERLAY_SENTIMENT,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_NO_COVERAGE,
    TR_WINDOW_ADVISOR_ENTERTAINMENT_FULL_COVERAGE,
    TR_TOOLTIP_ADVISOR_TRADE_LAND_POLICY,
    TR_TOOLTIP_ADVISOR_TRADE_LAND_POLICY_REQUIRED,
    TR_TOOLTIP_ADVISOR_TRADE_SEA_POLICY,
    TR_TOOLTIP_ADVISOR_TRADE_SEA_POLICY_REQUIRED,
    TR_TOOLTIP_HOLD_GAME,
    TR_TOOLTIP_NO_GAME,
    TR_WARNING_NEARBY_WOLF,
    TR_MARKET_TRADING,
    TR_MARKET_NOT_TRADING,
    TR_TEMPLE_DISTRIBUTING,
    TR_TEMPLE_NOT_DISTRIBUTING,
    TR_ADVISOR_CHIEF_NO_IMMIGRATION_SQUALOR,
    TR_CITY_MESSAGE_SQUALOR,
    TR_FIGURE_TYPE_LIGHTHOUSE_SUPPLIER,
    TR_WINDOW_ADVISOR_RELIGION_LARARIUMS,
    TR_WINDOW_RACE_YOUR_BET,
	TR_WINDOW_RACE_BET_BUTTON,
    TR_WINDOW_IN_PROGRESS_BET_BUTTON,
    TR_WINDOW_RACE_BET_TITLE,
    TR_WINDOW_RACE_BET_AMOUNT,
    TR_WINDOW_RACE_BET_DESCRIPTION,
    TR_WARNING_BET_VICTORY,
    TR_WARNING_BET_DEFEAT,
    TR_PERSONAL_SAVINGS,
    TR_WINDOW_RACE_BET_BLUE_HORSE,
    TR_WINDOW_RACE_BET_RED_HORSE,
    TR_WINDOW_RACE_BET_WHITE_HORSE,
    TR_WINDOW_RACE_BET_GREEN_HORSE,
    TR_BUILDING_GRAND_TEMPLE_NEEDS_WORKERS,
    TR_BUILDING_COLOSSEUM_NEEDS_WORKERS,
    TR_BUILDING_HIPPODROME_NEEDS_WORKERS,
    TR_BUILDING_LIGHTHOUSE_NEEDS_WORKERS,
    TR_BUILDING_CARAVANSERAI_NEEDS_WORKERS,
    TR_BUILDING_ROOFED_GARDEN_WALL,
    TR_BUILDING_GARDEN_WALL_GATE,
    TR_BUILDING_GARDEN_WALL_GATE_DESC,
    TR_WINDOW_BUILDING_DISTRIBUTION_CART_PUSHER_GETTING,
    TR_BUILDING_PALISADE,
    TR_BUILDING_PALISADE_DESC,
    TR_TOOLTIP_BUTTON_ACCEPT_WORKERS,
    TR_TOOLTIP_BUTTON_STOCKPILING_ON,
    TR_TOOLTIP_BUTTON_STOCKPILING_OFF,
    TR_OVERLAY_MOTHBALL,
    TR_OVERLAY_ENEMY,
    TR_BUILDING_TAVERN_DESC_5,
    TR_OVERLAY_WAREHOUSES,
    TR_WINDOW_RACE_BLUE_HORSE_DESCRIPTION,
    TR_WINDOW_RACE_RED_HORSE_DESCRIPTION, 
    TR_WINDOW_RACE_WHITE_HORSE_DESCRIPTION,
    TR_WINDOW_RACE_GREEN_HORSE_DESCRIPTION,
    TR_TOOLTIP_BUTTON_REJECT_WORKERS,
    TR_CONFIG_DIGIT_SEPARATOR,
    TR_TOOLTIP_OVERLAY_PROBLEMS_NO_LABOR,
    TR_WINDOW_BUILDING_DISTRIBUTION_GRANARY_CART_PUSHER_GETTING,
    TR_WINDOW_BUILDING_DISTRIBUTION_CART_PUSHER_RETURNING_WITH,
    TR_BUTTON_YEARLY_AUTOSAVE_OFF,
    TR_BUTTON_YEARLY_AUTOSAVE_ON,
    TR_BUILDING_DOCK_PLAGUE_DESC,
    TR_BUILDING_GRANARY_PLAGUE_DESC,
    TR_BUILDING_WAREHOUSE_PLAGUE_DESC,
    TR_BUILDING_FUMIGATION_DESC,
    TR_OVERLAY_SICKNESS,
    TR_ADVISOR_SICKNESS_LEVEL_LOW,
    TR_ADVISOR_SICKNESS_LEVEL_MEDIUM,
    TR_ADVISOR_SICKNESS_LEVEL_HIGH,
    TR_ADVISOR_SICKNESS_LEVEL_PLAGUE,
    TR_TOOLTIP_OVERLAY_SICKNESS_LOW,
    TR_TOOLTIP_OVERLAY_SICKNESS_MEDIUM,
    TR_TOOLTIP_OVERLAY_SICKNESS_HIGH,
    TR_TOOLTIP_OVERLAY_SICKNESS_PLAGUE,
    TR_CITY_MESSAGE_TITLE_SICKNESS,
    TR_CITY_MESSAGE_TEXT_SICKNESS,
    TR_FIGURES_CARTPUSHER_GOING_TO_ROME,
    TR_CITY_WARNING_DATA_COPY_SUCCESS,
    TR_CITY_WARNING_DATA_COPY_NOT_SUPPORTED,
    TR_CITY_WARNING_DATA_PASTE_SUCCESS,
    TR_CITY_WARNING_DATA_PASTE_NOT_SUPPORTED,
    TR_HOTKEY_SHOW_OVERLAY_FOOD_STOCKS,
    TR_HOTKEY_SHOW_OVERLAY_ENTERTAINMENT,
    TR_HOTKEY_SHOW_OVERLAY_SCHOOL,
    TR_HOTKEY_SHOW_OVERLAY_LIBRARY,
    TR_HOTKEY_SHOW_OVERLAY_ACADEMY,
    TR_HOTKEY_SHOW_OVERLAY_BARBER,
    TR_HOTKEY_SHOW_OVERLAY_BATHHOUSE,
    TR_HOTKEY_SHOW_OVERLAY_CLINIC,
    TR_HOTKEY_SHOW_OVERLAY_SICKNESS,
    TR_HOTKEY_SHOW_OVERLAY_TAX_INCOME,
    TR_HOTKEY_SHOW_OVERLAY_RELIGION,
    TR_HOTKEY_SHOW_OVERLAY_ROADS,
    TR_HOTKEY_ROTATE_MAP_NORTH,
    TR_HOTKEY_BUILD_WHEAT_FARM,
    TR_HOTKEY_SHOW_MESSAGES,
    TR_HOTKEY_SHOW_EMPIRE_MAP,
    TRANSLATION_MAX_KEY,
} translation_key;

typedef struct {
    translation_key key;
    const char *string;
} translation_string;

void translation_load(language_type language);

uint8_t *translation_for(translation_key key);

void translation_english(const translation_string **strings, int *num_strings);
void translation_french(const translation_string **strings, int *num_strings);
void translation_german(const translation_string **strings, int *num_strings);
void translation_italian(const translation_string **strings, int *num_strings);
void translation_korean(const translation_string **strings, int *num_strings);
void translation_polish(const translation_string **strings, int *num_strings);
void translation_portuguese(const translation_string **strings, int *num_strings);
void translation_russian(const translation_string **strings, int *num_strings);
void translation_spanish(const translation_string **strings, int *num_strings);
void translation_simplified_chinese(const translation_string **strings, int *num_strings);
void translation_swedish(const translation_string **strings, int *num_strings);
void translation_traditional_chinese(const translation_string **strings, int *num_strings);

#endif // TRANSLATION_TRANSLATION_H
