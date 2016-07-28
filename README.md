CDatabase Engine Learning
-------------------------

This is a very simple C applications that can currently create a database file named what you want, file extension doesn't matter.

command is like so 

./tpqdb [FILENAME] c

it has very basic commands to Create, Get, List and Delete records.

command for these are as follows:

Create:
./tpqdb [FILENAME] s [RECORDID] [FIELD1] [FIELD2] [FIELD3]

Get:
./tpqdb [FILENAME] g [RECORDID]

List:
./tpqdb [FILENAME] l

Delete:
./tpqdb [FILENAME] d [RECORDID]

Maximum row count is currently set to 1000
Maximum data length is currently set to 512 for every field.