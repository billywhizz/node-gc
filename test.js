var sys = require("sys");
var gc = require("./gc");

var GC = new gc.GC();
sys.puts(sys.inspect(GC, true, 10));
GC.collect();
