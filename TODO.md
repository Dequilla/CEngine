# TODO

##### -- No particular order --

### Some generic TODO's
- [ ] Create build script for linux to shave of testing time
- [ ] Create build script for windows
- [ ] Fix CMakeLists.txt topmost file, debug - release not working when building

- [ ] Create Renderer3D extendable to ForwardRenderer and later DeferredRenderer ONGOING
- [ ] Test and make sure models shared_ptr to mesh's are working like intended and so that we have no memory leak

- [ ] Finish documenting everything that is yet to be documented (doxygen)

### Material - Shader (Needs to be worked on somewhat in harmony/at the same time)
- [ ] Extend/Rebuild Material struct to support everything commented above it (as not hardcoded as possible) in Material.h
- [ ] Include possibility to have geometry shaders (low priority currently)

- [ ] In mesh only load materials once
- [ ] ModelLoader, texture, make sure we only load textures once so we don't fill memory with duplicates
