#/bin/bash
echo "The number of users logged into the system is:"
who | wc -l | cut -f 8 -d ' '
