#!/usr/bin/fish

for i in (seq $argv[1]);
    diff (./a.out < input$i.txt | psub) output$i.txt;
end;
