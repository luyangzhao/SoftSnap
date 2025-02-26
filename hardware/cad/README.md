# **SoftSnap CAD Models and 3D Printing Guide**  

## 🏗️ Overview  
This folder contains **3D models** for all key components of SoftSnap, enabling modular assembly for various soft robotic configurations.  

### **🔹 Full SoftSnap Module Assembly**
![SoftSnap Full Assembly](softsnap_module.png)  

---

## 📂 Files in this Folder  
- `3-in-1_motor_shell_part1.stl` → First part of the motor module shell.  
- `3-in-1_motor_shell_part2.stl` → Second part of the motor module shell.  
- `3-in-1_motor_module.step` → Full STEP file for modifying the motor module shell.  
- `Passive skeleton.stl` → Passive skeleton with customizable rib structure.  
- `Two-directional connector.stl` → Snap-together connector for modular assembly.  
- `softsnap_module.png` → Rendered image of the assembled SoftSnap system.  

---

## 🔩 **Component Descriptions**  

### **1️⃣ Passive Skeleton (`Passive skeleton.stl`)**  
- A flexible structure with **adjustable rib lengths, thickness, and middle rod dimensions** for customized mechanical properties.  
- Used for deformation-based actuation in SoftSnap robots.  

**🔧 Printing Guidelines:**  
- **Material**: TPU (Flexible Filament)  
- **Layer Height**: 0.1mm for flexibility  
- **Infill**: 100% recommended for strength  
- **Print Orientation**: Flat on the print bed  
- **Cooling**: Disable cooling fans for better adhesion  

---

### **2️⃣ 3-in-1 Motor Module Shell (`3-in-1_motor_shell_part1.stl`, `3-in-1_motor_shell_part2.stl`)**  
- Houses the **motor, PCB, and battery** for untethered operation and **Wi-Fi control**.  
- Includes **USB Type-C charging support**.  

**🔧 Printing Guidelines:**  
- **Material**: PLA, ABS, or resin (for high precision)  
- **Layer Height**: 0.1mm for finer details  
- **Infill**: 20-30% for structural balance  
- **Supports**: Required for overhangs  

🔹 **For modifications**, use `3-in-1_motor_module.step` in **Fusion 360, SolidWorks, or FreeCAD**.  

---

### **3️⃣ Two-Directional Connector (`Two-directional connector.stl`)**  
- Connects the **passive skeleton** to the **motor module**.  
- Allows **easy snap-together assembly** for modular configurations.  

**🔧 Printing Guidelines:**  
- **Material**: PLA or PETG for strength  
- **Layer Height**: 0.1mm  
- **Infill**: 40% recommended  
- **Print Orientation**: Flat for best strength  

---

## 🛠️ **Assembly Instructions**  
1️⃣ Print all required **STL files** based on the printing guidelines.  
2️⃣ Assemble the **3-in-1 Motor Module** by inserting the **PCB, motor, and battery**.  
3️⃣ Attach the **passive skeleton** to the **motor module** using the **two-directional connector**.  
4️⃣ Secure the assembly using snap-fit connections.  
5️⃣ Verify alignment and test movement.  


---

## 🔧 **Modifying the CAD Models**  
- To edit the **motor module shell**, use `3-in-1_motor_module.step` in **Fusion 360, SolidWorks, or FreeCAD**.  
- To modify the **passive skeleton**, adjust the `Passive skeleton.stl` file to experiment with different rib configurations.  
- To customize the **connector**, modify `Two-directional connector.stl` to fit alternative module sizes.  
