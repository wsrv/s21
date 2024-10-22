#!/bin/bash

echo -e "${background1}${font1}hostname\e[0m = ${background2}${font2}$HOSTNAME\e[0m"
echo -e "${background1}${font1}timezone\e[0m = ${background2}${font2}$TZ\e[0m"
echo -e "${background1}${font1}user\e[0m = ${background2}${font2}$USER\e[0m"
echo -e "${background1}${font1}OS\e[0m = ${background2}${font2}$OS\e[0m"
echo -e "${background1}${font1}date\e[0m = ${background2}${font2}$date\e[0m"
echo -e "${background1}${font1}uptime\e[0m = ${background2}${font2}$time\e[0m"
echo -e "${background1}${font1}uptime_sec\e[0m = ${background2}${font2}$total_seconds sec\e[0m"
echo -e "${background1}${font1}IP\e[0m = ${background2}${font2}$ip\e[0m"
echo -e "${background1}${font1}MASK\e[0m = ${background2}${font2}$mask\e[0m"
echo -e "${background1}${font1}GATEWAY\e[0m = ${background2}${font2}$gateway\e[0m"
echo -e "${background1}${font1}RAM_TOTAL\e[0m = ${background2}${font2}$ram_total\e[0m"
echo -e "${background1}${font1}RAM_USED\e[0m = ${background2}${font2}$ram_used\e[0m"
echo -e "${background1}${font1}RAM_FREE\e[0m = ${background2}${font2}$ram_free\e[0m"
echo -e "${background1}${font1}SPACE_ROOT\e[0m = ${background2}${font2}$space_root\e[0m"
echo -e "${background1}${font1}SPACE_ROOT_USED\e[0m = ${background2}${font2}$space_root_used\e[0m"
echo -e "${background1}${font1}SPACE_ROOT_FREE\e[0m = ${background2}${font2}$space_root_free\e[0m"

echo ""

echo "Column 1 background = ${color_num_back1} ${color_name_back1}"
echo "Column 1 font color = ${color_num_font1} ${color_name_font1}"
echo "Column 2 background = ${color_num_back2} ${color_name_back2}"
echo "Column 2 font color = ${color_num_font2} ${color_name_font2}"

