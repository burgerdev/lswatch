#!/usr/bin/env python

import sys
import watchio


if sys.version_info[0] is not 3:
	watchio.error("Python version is not 3.")
	sys.exit(1)
	
