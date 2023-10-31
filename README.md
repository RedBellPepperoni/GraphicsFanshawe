# Physics Midterms
 The Submission for the Phyics 1 midterms


 # instructions 

Step 1 : Compile the [GraphicsCode] Project first
Step 2 : Then setup the [Physics_Midterm] project as startup project
Step 3 : Build + run the project


# controls

[W] [A] [S] [D] for camera movement

Hold [RightClick] for view movement

Press [Spacebar] to activate shield

Use [G] to Pause/Start the Physics Sim


## =============== Important ===================

All the Loading and transform setting is in the Graphic midterm project: Navigate to the [Physics_Midterm/Source/PhysicsApp.cpp]


The [Physics_Midterms] project should have the Asteroid, explosion implementation.




All the physics code can be found in [GraphicsCode/Source/Engine/Core/Physics/] folder

The System is didved into 2 stages [BroadPhase] and [NarrowPhase]

These can be found in [GraphicsCode/Source/Engine/Core/Physics/Collision/BroadPhase/] and
[GraphicsCode/Source/Engine/Core/Physics/Collision/NarrowPhase/] respectively

Currenly using a naive broadphase, where it bruteforces through all the aabbs.

The Collision System is based upon Sperated Axis Theorm, and the code for taht is in NarrowPhase


The MeshCollider class creates  its own custom Convex hull using the mesh indicies and vertices
That can be found in [GraphicsCode/Source/Engine/Core/Physics/Collision/Colliders/MeshCollider.h]



## === NOTES =============


