
# addon meta data info
bl_info = {
    "name": "Custom L-System Generator",
    "author": "Chris M",
    "version": (1, 0),
    "blender": (4, 4, 0),
    "description": "Generates 3D fractal structures using an L-system with stack-based branching and full 3D turtle rotations, output as beveled curves.",
    "category": "Add Mesh",
}

import bpy
from bpy.props import StringProperty, IntProperty, FloatProperty, PointerProperty
from bpy.types import Operator, Panel, PropertyGroup
import math
from mathutils import Vector, Quaternion

#   property group for L-system settings
#   defines all parameters 
class LSystemSettings(PropertyGroup):
    axiom: StringProperty(
        name="Axiom",
        description="starting string for the L-system",
        default="A"
    )
    variables: StringProperty(
        name="Variables",
        description="symbols that make forward movement/drawing",
        default="ABF"
    )
    constants: StringProperty(
        name="Constants",
        description="symbols that do not draw (rotations, etc)",
        default="+-&^\\/|[]"
    )
    rule_F: StringProperty(
        name="Rule for F",
        description="place holder for 'F'",
        default="F-F++F-F"
    )
    rule_A: StringProperty(
        name="Rule for A",
        description="place holder for 'A'",
        default="B-A-B"
    )
    rule_B: StringProperty(
        name="Rule for B",
        description="place holder for 'B'",
        default="A+B+A"
    )
    iterations: IntProperty(
        name="Iterations",
        description="number of times it rewrites",
        default=1,
        min=0
    )
    angle: FloatProperty(
        name="Angle (deg)",
        description="rotation angle",
        default=60.0,
        min=0.0,
        max=360.0
    )
    step: FloatProperty(
        name="Step Length",
        description="distance moved",
        default=1.0,
        min=0.0
    )
    bevel_depth: FloatProperty(
        name="Thickness",
        description="thickness of the lines",
        default=0.05,
        min=0.0
    )

# operator to make the L-system


class OBJECT_OT_lsystem_generate(Operator):
    bl_idname = "object.lsystem_generate"
    bl_label = "Generate L-system"
    bl_description = "makes a 3D plant from the L-system settings"
    bl_options = {'REGISTER', 'UNDO'}

    def execute(self, context):
        props = context.scene.lsystem_settings
        
        
        # build rewrite rules dict dict dict dict
        rules = {'F': props.rule_F, 'A': props.rule_A, 'B': props.rule_B}
        
        
        # rewriting the axiom
        sequence = props.axiom
        
        #string rewriting for each iteration
        for _ in range(props.iterations):
            sequence = "".join(rules.get(ch, ch) for ch in sequence)

        # create the curve data
        curve_data = bpy.data.curves.new("LSystemCurve", 'CURVE')
        curve_data.dimensions = '3D'
        
        #bevel depth give us thickness to the plants
        curve_data.bevel_depth = props.bevel_depth
        curve_obj = bpy.data.objects.new("LSystem", curve_data)
        context.collection.objects.link(curve_obj)

        # prepare 3D turtle graphics (drawing)
        
        #use quaternion to keep position and orientationat
        position = Vector((0.0, 0.0, 0.0))
        orientation = Quaternion((1.0, 0.0, 0.0, 0.0)) 
        
        
        angle_rad = math.radians(props.angle)
        stack = []
        paths = []
        current_path = [position.copy()]




# 
        def new_path():
            
            #non local used to modify current_path from execute
            nonlocal current_path
            
            #keeping track if the turtle actually moved some where 
        
            if len(current_path) > 1:
                paths.append(current_path)
                #start new path at new position
            current_path = [position.copy()]


        # interpret sequence
        for ch in sequence:
            if ch in props.variables:
                
                
                # DRAWING forward
                dir_vec = orientation @ Vector((0.0, props.step, 0.0))
                position += dir_vec
                current_path.append(position.copy())
                
                
                
                
            elif ch == '+':  # rotate around z axis left
                axis = orientation @ Vector((0, 0, 1))
                orientation = Quaternion(axis, angle_rad) @ orientation
            elif ch == '-':  # rotate around the z axis right
                axis = orientation @ Vector((0, 0, 1))
                orientation = Quaternion(axis, -angle_rad) @ orientation
                
                
            elif ch == '&':  # pitch down around the x axis
                axis = orientation @ Vector((1, 0, 0))
                orientation = Quaternion(axis, angle_rad) @ orientation
            elif ch == '^':  # pitch up aroundthe  x axis
                axis = orientation @ Vector((1, 0, 0))
                orientation = Quaternion(axis, -angle_rad) @ orientation
                
                
            elif ch == '\\':  # rotate left around the y axis
                axis = orientation @ Vector((0, 1, 0))
                orientation = Quaternion(axis, angle_rad) @ orientation
            elif ch == '/':  # rotate right around the y axis
                axis = orientation @ Vector((0, 1, 0))
                orientation = Quaternion(axis, -angle_rad) @ orientation
                
                
            elif ch == '|':  # flips direction (symmetry tool)
                axis = orientation @ Vector((0, 0, 1))
                orientation = Quaternion(axis, math.pi) @ orientation
                
                
            elif ch == '[':  # grouping symbol start
                stack.append((position.copy(), orientation.copy()))
                new_path()
            elif ch == ']':  # grouping symbol end
                new_path()
                position, orientation = stack.pop()
                
    #end the branch
        new_path()



        # Create splines
        for path in paths:
            spline = curve_data.splines.new('POLY')
            spline.points.add(len(path) - 1)
            for i, pt in enumerate(path):
                spline.points[i].co = (pt.x, pt.y, pt.z, 1)

        return {'FINISHED'}

# ui panel for the side bar. settings, parameters and options
class VIEW3D_PT_lsystem_panel(Panel):
    bl_label = "L-System Generator"
    bl_idname = "VIEW3D_PT_lsystem_panel"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = 'L-System'

    def draw(self, context):
        layout = self.layout
        props = context.scene.lsystem_settings
        layout.prop(props, "axiom")
        layout.prop(props, "variables")
        layout.prop(props, "constants")
        layout.prop(props, "rule_F")
        layout.prop(props, "rule_A")
        layout.prop(props, "rule_B")
        layout.prop(props, "iterations")
        layout.prop(props, "angle")
        layout.prop(props, "step")
        layout.prop(props, "bevel_depth")#thickness
        layout.operator("object.lsystem_generate", icon='CURVE_DATA')





# registration
classes = (
    LSystemSettings,
    OBJECT_OT_lsystem_generate,
    VIEW3D_PT_lsystem_panel,
)




# more addon registration
def register():
    for cls in classes:
        bpy.utils.register_class(cls)
    bpy.types.Scene.lsystem_settings = PointerProperty(type=LSystemSettings)


def unregister():
    del bpy.types.Scene.lsystem_settings
    for cls in reversed(classes):
        bpy.utils.unregister_class(cls)

if __name__ == "__main__":
    register()
