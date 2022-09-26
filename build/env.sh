rm -f ../setup_info.h
cat <<EOF >../setup_info.h
#define ROOT "@PROJECT_SOURCE_DIR@"
#define DEBUG true
EOF
cmake -GNinja  ./..