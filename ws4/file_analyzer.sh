
text_files=0
image_files=0
shell_scripts=0
data_files=0
other_files=0

for i in "$@"
do
    file_type=$(echo $i | cut -d '.' -f2)
    case $file_type in
        "txt"|"md") 
            ((text_files++))
            ;;
        "jpg"|"png"|"gif") 
            ((image_files++))
            ;;
        "sh") 
            ((shell_scripts++))
            ;;

        "csv"|"json") 
            ((data_files++))
            ;;
        *)
        ((other_files++))
        ;;
    esac
done
echo "Text files: $text_files"
echo "Image files: $image_files"
echo "Shell scripts: $shell_scripts"
echo "Data files: $data_files"
echo "Other files: $other_files"