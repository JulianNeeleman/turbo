# Make the packages directory if it doesn't exist.
mkdir -p packages/${1}

# Run preprocessor with correct flags.
g++ -E -nostdinc -Dinclude=#include -I. -Isystem_headers submissions/${1}/${2}.cpp | grep -v '^# [0-9]' > packages/${1}/${2}.cpp
