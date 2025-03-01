# **SoftSnap Hardware: CAD Models & PCB Design**  

## 🏗️ Overview  
This folder contains **hardware-related files** for the SoftSnap modular robotics system, including **3D models (CAD)** for robot components and **PCB designs** for the control system.

---

## 📂 Folder Structure  
```
hardware/  
├── pcb/                     # PCB design files  
│   ├── pcb_render.png        # PCB design image  
│   ├── README.md             # PCB documentation & OSHWHub link  
├── cad/                     # 3D models and mechanical design  
│   ├── softsnap_module.png   # Full SoftSnap module image  
│   ├── Passive skeleton.stl  # SoftSnap passive skeleton  
│   ├── Two-directional connector.stl  # Snap-fit connector  
│   ├── 3-in-1_motor_shell_part1.stl  # Motor module shell (part 1)  
│   ├── 3-in-1_motor_shell_part2.stl  # Motor module shell (part 2)  
│   ├── README.md             # CAD printing & assembly guide  
```

---

## 🔩 **Hardware Components**  

### **1️⃣ SoftSnap Passive Skeleton**  
- A flexible TPU-based structure allowing **modular deformation**.  
- Adjustable rib lengths, thickness, and configurations for different actuation patterns.  
- File: `Passive skeleton.stl`  

### **2️⃣ 3-in-1 Motor Module Shell**  
- Protective casing for the **motor, PCB, and battery**.  
- Two-part design for easy **3D printing and assembly**.  
- Files: `3-in-1_motor_shell_part1.stl`, `3-in-1_motor_shell_part2.stl`  

### **3️⃣ Two-Directional Connector**  
- Snap-fit connector allowing **easy modular attachment** of SoftSnap components.  
- File: `Two-directional connector.stl`  

### **4️⃣ PCB Design**  
- Custom PCB for **motor control, wireless communication, and battery management**.  
- The full design is available on **OSHWHub**:  
  👉 [SoftSnap PCB Design on OSHWHub](https://oshwhub.com/cccat/universal-design)  
- File: `pcb_render.png` (preview image)  

---

## 🔧 **Modifications & Customization**  
- To **modify the mechanical design**, use the `.step` files in **Fusion 360, SolidWorks, or FreeCAD**.  
- To **adjust the PCB**, download the source files from OSHWHub.  

---

## 📜 License  
📜 This project is licensed under the **MIT License**.  
