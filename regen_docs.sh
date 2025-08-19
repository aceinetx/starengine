#!/usr/bin/bash
rm -rf docs
doxygen Doxyfile
mv docs/html/* docs
rmdir docs/html
