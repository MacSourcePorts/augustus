# game/app specific values
export APP_VERSION="3.1.0"
export ICONSDIR="res"
export ICONSFILENAME="augustus"
export PRODUCT_NAME="augustus"
export EXECUTABLE_NAME="augustus"
export PKGINFO="APPLAUGS"
export COPYRIGHT_TEXT="Caesar Copyright © 1998 Impressions Games. All rights reserved."

#constants
source ../MSPScripts/constants.sh

rm -rf ${BUILT_PRODUCTS_DIR}

# create makefiles with cmake, perform builds with make
rm -rf ${X86_64_BUILD_FOLDER}
mkdir ${X86_64_BUILD_FOLDER}
cd ${X86_64_BUILD_FOLDER}
/usr/local/bin/cmake ..
make -j$NCPU

cd ..
rm -rf ${ARM64_BUILD_FOLDER}
mkdir ${ARM64_BUILD_FOLDER}
cd ${ARM64_BUILD_FOLDER}
cmake ..
make -j$NCPU

cd ..

# create the app bundle
"../MSPScripts/build_app_bundle.sh"

#sign and notarize
"../MSPScripts/sign_and_notarize.sh" "$1"