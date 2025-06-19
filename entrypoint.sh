#!/bin/sh

set -e

# move and do not overwrite existing files
mv -vn /usr/local/bin/resources/* /opt/alicia-server/

exec "$@"
