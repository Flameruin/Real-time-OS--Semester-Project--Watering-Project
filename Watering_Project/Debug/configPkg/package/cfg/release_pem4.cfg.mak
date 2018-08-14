# invoke SourceDir generated makefile for release.pem4
release.pem4: .libraries,release.pem4
.libraries,release.pem4: package/cfg/release_pem4.xdl
	$(MAKE) -f C:\Users\haite\workspace_v7\Watering_Project/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\haite\workspace_v7\Watering_Project/src/makefile.libs clean

