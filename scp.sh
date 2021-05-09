#!/bin/bash

# Used to copy project to brake (for Erlend)

scp -r /home/erlend/projects/k-means efo047@login.uib.no:/Home/siv32/efo047 && ssh efo047@login.uib.no 'scp -r k-means efo047@brake.ii.uib.no:/Home/siv32/efo047'