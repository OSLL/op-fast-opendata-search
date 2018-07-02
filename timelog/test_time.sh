#!/bin/bash

#clean log file:
echo -n > ./timelog/running_time.log
echo "Текущая дата и время:" >> ./timelog/running_time.log
date >> ./timelog/running_time.log
echo "Анализ поиска в разных режимах" >> ./timelog/running_time.log
echo "" >> ./timelog/running_time.log
for query in "памятник" "дворец" "мост" "Аничков мост" ""
    do
    for index in 1 2 3
        do
        echo "-search , query is $query, attempt #$index" >> ./timelog/running_time.log
        /usr/bin/time  -o ./timelog/running_time.log --append ./opendata_search.out -search "$query"
        echo "" >> ./timelog/running_time.log
        echo "-search with limits , query is $query, attempt #$index" >> ./timelog/running_time.log
        for lim in 100 50 5 1
            do
            echo "Limit is $lim" >> ./timelog/running_time.log
            /usr/bin/time  -o ./timelog/running_time.log --append ./opendata_search.out -search "$query" -limit $lim
            echo "" >> ./timelog/running_time.log
            done
        echo "-complexsearch , query is $query, attempt #$index" >> ./timelog/running_time.log
        /usr/bin/time  -o ./timelog/running_time.log --append ./opendata_search.out -complexsearch "$query"
        echo "" >> ./timelog/running_time.log
        done
    done
echo "Анализ поиска по координатам" >> ./timelog/running_time.log
for query in "59,30,10000" "59.0,30.0,5000" "59.934616,30.316211,2000" "59.934616, 30.316211,300", ""
    do
    for index in 1 2 3
        do
        echo "-geosearch , query is $query, attempt #$index" >> ./timelog/running_time.log
        /usr/bin/time  -o ./timelog/running_time.log --append ./opendata_search.out -geosearch "$query"
        echo "" >> ./timelog/running_time.log
        echo "-geosearch with limits , query is $query, attempt #$index" >> ./timelog/running_time.log
        for lim in 100 50 5 1
            do
            echo "Limit is $lim" >> ./timelog/running_time.log
            /usr/bin/time  -o ./timelog/running_time.log --append ./opendata_search.out -geosearch "$query" -limit $lim
            echo "" >> ./timelog/running_time.log
            done
        done
    done
