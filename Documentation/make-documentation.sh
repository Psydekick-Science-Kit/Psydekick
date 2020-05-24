#!/bin/bash

doxygen doxyfile
doxyrest_b/build/doxyrest/bin/Release/doxyrest
sphinx-build -b html rst html
