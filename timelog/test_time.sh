#!/bin/bash

#clean log file:
echo -n > ./timelog/running_time.log
echo "Текущая дата и время:" >> ./timelog/running_time.log
date >> ./timelog/running_time.log
echo "Анализ поиска в разных режимах" >> ./timelog/running_time.log
echo "" >> ./timelog/running_time.log
for query in "памятник" "дворец" "Дворец"
    do
    for index in 1 2 3 4 5
        do
        echo "-search , query is $query, attempt #$index" >> ./timelog/running_time.log
        /usr/bin/time  -o ./timelog/running_time.log --append ./opendata_search.out -search "$query"
        echo "" >> ./timelog/running_time.log
        echo "-complexsearch , query is $query, attempt #$index" >> ./timelog/running_time.log
        /usr/bin/time  -o ./timelog/running_time.log --append ./opendata_search.out -complexsearch "$query"
        echo "" >> ./timelog/running_time.log
        done
    done
