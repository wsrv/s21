REGEX="^[+-]?[0-9]+([.][0-9]+)?$"
if [[ ! $1 =~ $REGEX ]]; then
    exit 1
else
exit 0
fi