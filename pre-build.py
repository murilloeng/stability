#imports
import os

#commands
uic = "%QT_HOME%\\bin\\uic.exe"
rcc = "%QT_HOME%\\bin\\rcc.exe"

#uic files
for root, dirs, files in os.walk("ui"):
	for file in files:
		src_path = os.path.join(root, file)
		obj_path = src_path.replace(".ui", ".hpp")
		obj_path = obj_path.replace("ui\\", "build\\uic\\")
		os.makedirs(os.path.dirname(obj_path), exist_ok = True)
		if not os.path.isfile(obj_path) or os.path.getmtime(src_path) > os.path.getmtime(obj_path):
			os.system("%s -o %s %s" % (uic, obj_path, src_path))

#rsc files
for root, dirs, files in os.walk("rsc"):
	for file in files:
		if file.endswith(".qrc"):
			src_path = os.path.join(root, file)
			obj_path = src_path.replace(".qrc", ".cpp")
			obj_path = obj_path.replace("rsc\\", "build\\rsc\\")
			os.makedirs(os.path.dirname(obj_path), exist_ok = True)
			if not os.path.isfile(obj_path) or os.path.getmtime(src_path) > os.path.getmtime(obj_path):
				os.system("%s -o %s %s" % (rcc, obj_path, src_path))