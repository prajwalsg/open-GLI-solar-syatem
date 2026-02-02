# open-GLI-solar-syatem
Hierarchical 3D Solar System Simulation using OpenGL
1. Core Architecture: The Scene Graph
Instead of manually calculating absolute coordinates (e.g., Earth at 5,3,5) for every frame, the simulation
implements a Scene Graph structure.
• Concept: The system is modelled as a tree data structure where transformations propagate downwards
from the root to the leaves.
• The Root (Global Origin): The Sun acts as the root node at World Space (0,0,0).
• Relative Positioning: All child objects define their position relative to their parent's local coordinate
system.
o Sun -> Earth (Earth inherits Sun's transformations)
o Earth -> Moon (Moon inherits Earth's transformations)
<img width="1157" height="591" alt="image" src="https://github.com/user-attachments/assets/faad4b0b-5448-463a-9566-2bc7845efac5" />

2. Implementation: The Matrix Stack
To implement the parent-child relationship, I utilize the OpenGL Matrix Stack (glPushMatrix and glPopMatrix).
• State Preservation: glPushMatrix() saves the current state of the coordinate system (the parent's
position/rotation).
• Local Transformation: Once the state is saved, I apply transformations to move to the child's location.
• Restoration: After drawing the child (and its children), glPopMatrix() restores the coordinate system to
the parent's state, isolating the branches of the hierarchy.

3. Transformation Pipeline (Affine Transformations)
Movements are achieved by manipulating the ModelView Matrix. The order of operations is critical (non-
commutative):
• A. Rotation (glRotatef) - The Orbital Mechanism:
o To simulate an orbit, I rotate the coordinate system before translating.
o Technical Detail: By rotating the grid around the Y-axis and then translating along the X-axis, the
object naturally moves in a circular path around the parent.
• B. Translation (glTranslatef) - The Radius:
o This defines the orbital distance. Instead of hardcoding a coordinate like (5,3,5), I translate by a
scalar value (Radius $r$) along the local axis.
• C. Scaling (glScalef):
o Applied last to define the relative volume of the spheres without affecting the orbital distances.

4. Illumination Model (Phong Lighting)
To render 3D depth, I implement the standard OpenGL lighting model (Gouraud/Phong).
• Light Source (GL_LIGHT0):
o A Point Light is placed at the origin (0,0,0). This ensures realistic omnidirectional lighting where
the side of the planet facing the Sun is illuminated, and the opposite side is in shadow.
• Material Properties (glMaterialfv):
o Emission (GL_EMISSION): Applied only to the Sun. This allows the Sun to appear bright/glowing
even though it is not illuminated by an external source.
o Diffuse (GL_DIFFUSE): Applied to planets to scatter light, revealing their spherical shape.
o Specular (GL_SPECULAR): Applied to the Earth to simulate the reflection of the sun on water
surfaces (shininess).

Summary of Technical Flow
1. Initialize: Enable GL_DEPTH_TEST (Z-buffering) and GL_LIGHTING.
2. Render Loop:
o Push Matrix (Save World Origin).
o Apply Emission -> Draw Sun.
o Rotate (Earth Orbit) -> Translate (Earth Radius) -> Push Matrix (Save Earth Pos).
o Apply Diffuse/Specular -> Draw Earth.
o Rotate (Moon Orbit) -> Translate (Moon Radius) -> Draw Moon.
o Pop Matrix (Return to Earth) -> Pop Matrix (Return to Sun).
3. Swap Buffers: Display the rendered frame.


<img width="1100" height="582" alt="image" src="https://github.com/user-attachments/assets/22ba6616-182b-4748-ad90-3d4354b3b0c7" />
