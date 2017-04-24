#!/usr/bin/env python3

import xmlPaser as xp
import xmlReceiver as xr
from queue import Queue

QUE = Queue();
xr.xmlReceive(QUE);

