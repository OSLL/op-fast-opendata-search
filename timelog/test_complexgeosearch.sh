#!/bin/bash

#clean log file:
echo -n > ./timelog/geosearch_running_time.log
echo "Текущая дата и время:" >> ./timelog/geosearch_running_time.log
date >> ./timelog/geosearch_running_time.log
echo "Анализ сложного геопоиска" >> ./timelog/geosearch_running_time.log
echo "" >> ./timelog/geosearch_running_time.log
for query in "59.938630, 30.314130, 1" "59.938630, 30.314130, 100" "59.938630, 30.314130, 500" "59.938630, 30.314130, 2500" "59.938630, 30.314130, 5000" "59.938630, 30.314130, 10000"
    do
    for index in 1 2 3
        do
        echo "-complexgeosearch , query is $query, attempt #$index" >> ./timelog/geosearch_running_time.log
        /usr/bin/time  -o ./timelog/geosearch_running_time.log --append ./opendata_search.out -complexgeosearch "$query"
        echo "" >> ./timelog/geosearch_running_time.log
    done
done
