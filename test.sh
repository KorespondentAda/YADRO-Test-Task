#!/bin/bash

exec $1 $2 | diff - $3
