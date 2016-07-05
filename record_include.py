
ui_conf_gen = file("generated-src/cpp/ui_conf_gen.hpp", "r+")

lines = []
for line in ui_conf_gen:
	lines.append(line.strip()+"\n")
	#print lines[-1]

ui_conf_gen.close()

ui_conf_gen = file("generated-src/cpp/ui_conf_gen.hpp", "w")

for line in lines:
	#print line
	if -1 == line.find("struct ViewConf;"):
		ui_conf_gen.writelines(line)
	if -1 != line.find("pragma"):
		print "write #include \"view_conf.hpp\""
		ui_conf_gen.writelines("#include \"view_conf.hpp\"")

ui_conf_gen.close()
print "process end"