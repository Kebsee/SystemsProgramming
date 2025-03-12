ppl='John,25,Engineer\nYusuf,24,CEO\nSundar,21,Founder\nYujiang,14,Grandmaster'
echo -e $ppl | cut -d, -f1 > name
echo -e $ppl | cut -d, -f3 > profession

paste name profession > name_prof


