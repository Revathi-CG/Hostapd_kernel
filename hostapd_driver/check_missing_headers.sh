#!/bin/bash

BASE_DIR=~/Desktop/Hostapd_kernel/hostapd_driver
PORTING_DIR=$BASE_DIR/porting

mkdir -p "$PORTING_DIR"

# Extract include paths from Makefile (-I flags)
INCLUDE_PATHS=$(grep -oP '(?<=-I)[^ ]+' Makefile)

echo "Using include paths:"
echo "$INCLUDE_PATHS"
echo "---------------------------------------"

CHECK_COUNT=0
CREATED_COUNT=0

while read -r inc; do
    [[ "$inc" != \#include* ]] && continue    # Skip non-include lines

    ((CHECK_COUNT++))

    # Extract file path (remove #include, remove <> or "")
    FILE=$(echo "$inc" | sed 's/#include//' | tr -d '<>"' | xargs)

    echo -n "[$CHECK_COUNT] Checking $FILE ... "

    FOUND=0

    # Search in include dirs from Makefile
    for DIR in $INCLUDE_PATHS; do

        # exact full path match
        if [[ -f "$BASE_DIR/$DIR/$FILE" ]]; then
            echo "✔ Found in $DIR"
            FOUND=1
            break
        fi

        # match only filename
        if [[ -f "$BASE_DIR/$DIR/$(basename "$FILE")" ]]; then
            echo "✔ Found loose match in $DIR"
            FOUND=1
            break
        fi
    done

    # If not found → create
    if [[ $FOUND -eq 0 ]]; then
        echo "❌ NOT FOUND → Creating in porting/"
        DEST_PATH="$PORTING_DIR/$FILE"
        mkdir -p "$(dirname "$DEST_PATH")"

        # GENERATE include guard only from filename
        BASE=$(basename "$FILE")
        GUARD=$(echo "$BASE" | tr '.-' '_' | tr '[:lower:]' '[:upper:]')
        GUARD="__${GUARD}_"

        # Write include guard to file
        cat << EOF > "$DEST_PATH"
#ifndef $GUARD
#define $GUARD

#endif /* $GUARD */
EOF

        echo "➡ Created: $DEST_PATH"
        ((CREATED_COUNT++))
    fi

done < includes_list.txt

echo "---------------------------------------"
echo "✅ Total includes processed : $CHECK_COUNT"
echo "⚠️ Missing headers created  : $CREATED_COUNT"

