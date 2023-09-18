#This script assume the the python venv in current directory and zephyrproject setup in the parent directory
source ./venv/bin/activate
source ../zephyrproject/zephyr/zephyr-env.sh
west zephyr-export
