# -- Path setup --------------------------------------------------------------

import os
import sys

sys.path.insert(0, os.path.abspath('../doxyrest_b/doxyrest/sphinx'))

# -- Project information -----------------------------------------------------

project = 'Psydekick'
copyright = '2020, Dominic Canare'
author = 'Dominic Canare'

# -- General configuration ---------------------------------------------------

extensions = ['doxyrest', 'cpplexer', 'sphinx_rtd_theme']
templates_path = ['_templates']
exclude_patterns = ['page_index.rst']

# -- Options for HTML output -------------------------------------------------

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
html_js_files = []
