#!/bin/bash
 echo "Content-type: text/html"
 echo ""
 echo "<html><head><title>mco</title></head><body>"
 echo "Start calling: $0 <br>"
/opt/puppetlabs/bin/mco shell -I /^sbob/ 'su bobs -c "/home/bobs/local/hooks/hook_script.sh &> /tmp/mco_sph.txt &"' 
 echo "End calling: $0 <br>"
 echo "</body></html>"
