# **SoftSnap: A Modular and Untethered Soft Robotics Platform**  

## 🚀 Overview  
SoftSnap is a **modular, untethered soft robotics system** designed for **rapid prototyping** and exploration of **bio-inspired locomotion and manipulation tasks**. It enables researchers, educators, and hobbyists to quickly assemble **snap-together robotic modules** with integrated **cable-driven actuation, onboard control, and wireless communication**.

This repository provides **open-source resources**, including:  
✅ **CAD models** for SoftSnap skeletons, connectors, and casing.  
✅ **PCB designs** for the integrated control system.  
✅ **Jupyter Notebook-based code** for forward and inverse simulation.  
✅ **Firmware and control scripts** for actuation and locomotion experiments.  
✅ **Assembly guidelines and tutorials** to build and modify SoftSnap robots.  

---

## 🔧 Features  
- 🛠 **Modular Design**: Easily snap together different modules to create robots like starfish-inspired, brittle-star locomotion, snake-like, grippers, and ring-based caging systems.  
- 🎛 **Cable-Driven Actuation**: Uses a **motorized winch system** to control flexible TPU-based skeleton deformation.  
- 📡 **Wireless Control**: Supports remote control via **Wi-Fi-based communication**.  
- 🔄 **Open-Source & Customizable**: Modify, 3D print, and expand the system to fit specific applications.  
- 🔬 **Simulation & Modeling**: Includes Jupyter Notebook tools for **predicting deformation behavior** and optimizing threading patterns.  

---

## 📂 Repository Structure  

📦 SoftSnap
├── hardware/ # CAD models & PCB design
├── software/ # Jupyter Notebook-based simulation & control code
├── firmware/ # Microcontroller firmware
├── docs/ # Assembly guide & tutorials
├── LICENSE # License file
├── README.md # This document

---

## 📦 Getting Started  

### 🔩 1️⃣ Hardware Requirements  
To build a SoftSnap module, you will need:  
- **3D-printed components** (TPU skeleton, PLA connectors, resin casing)  
- **Motor module** (GA12-N20 motor, PCB, Li-ion battery)  
- **fishing string**  


Refer to the **assembly guide** in the `docs/` folder for detailed instructions.  

### 🖥 2️⃣ Running the Jupyter Notebook Code  
The simulation, forward and inverse modeling, and control scripts are provided as Jupyter Notebooks for ease of use.  

1. Clone this repository:  
   ```bash
   git clone https://github.com/YOUR_GITHUB_USERNAME/SoftSnap.git  
   cd SoftSnap





