NOTE: THIS IS A WORK IN PROGRESS PROJECT FOR AN OPENGL AND VULKAN RENDERER

-CMake file included, minimum version of CMake is 3.19.
-Use CMake to build the project.
-The plan is to add this to my game engine project as a dll.

-Resource.h isnt used currently, it will be used as base class for all resources in the future. Containing file location as a string and the file type as a template object. This will be implimented once mesh and texture loading have been sorted out.

-A Resource loader is required, the issue is checking and separating types of resources will be complex. Additionally, with assimp added to the project, the idea of this gets more complex. Currently the plan is to wrap the assimp library into a 'mesh loader' which will be called from the resource loader. This will require a function to check the resource type before passing it through to the required functions. This method will be slow but may be the most simple and logical option.

-Finally, the files for the project need to be sorted into folders which will make it easier to read in the file explorer as well as linking related items together.