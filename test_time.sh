#!/bin/bash

#clean log file:
echo -n > ./running_time.log
echo "Текущая дата и время:" >> ./running_time.log
date >> ./running_time.log
echo "Анализ поиска в разных режимах" >> ./running_time.log
echo "" >> ./running_time.log
for query in "памятник" "дворец" "Дворец"
    do
    for index in 1 2 3 4 5
        do
        echo "-search , query is $query, attempt #$index" >> ./running_time.log
        /usr/bin/time  -o ./running_time.log --append ./opendata_search.out -search "$query"
        echo "" >> ./running_time.log
        echo "-complexsearch , query is $query, attempt #$index" >> ./running_time.log
        /usr/bin/time  -o ./running_time.log --append ./opendata_search.out -complexsearch "$query"
        echo "" >> ./running_time.log
        done
    done
