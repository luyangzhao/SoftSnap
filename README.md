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

```
📦 SoftSnap  
 ├── hardware/              # CAD models & PCB design  
 ├── software/              # Jupyter Notebook-based simulation & control code  
 ├── firmware/              # Microcontroller firmware  
 ├── docs/                  # Assembly guide & tutorials  
 ├── LICENSE                # License file  
 ├── README.md              # This document  
 ├── requirements.txt       # Python dependencies (if needed)  
```

---

## 📦 Getting Started  

### 🔩 1️⃣ Hardware Requirements  
To build a SoftSnap module, you will need:  
- **3D-printed components** (TPU skeleton, PLA connectors, resin casing)  
- **Motor module** (GA12-N20 motor, PCB, Li-ion battery)  
- **8-braid No. 2 PE fishing line** (0.23mm, 12.7 kg tensile strength)  
- **Microcontroller & Wi-Fi module** (for remote operation)  

Refer to the **assembly guide** in the `docs/` folder for detailed instructions.  

### 🖥 2️⃣ Running the Jupyter Notebook Code  
The simulation, forward and inverse modeling, and control scripts are provided as Jupyter Notebooks for ease of use.  

1. Clone this repository:  
   ```bash
   git clone https://github.com/YOUR_GITHUB_USERNAME/SoftSnap.git  
   cd SoftSnap
   ```  
2. Open the Jupyter Notebook:  
   ```bash
   jupyter notebook  
   ```  
3. Navigate to the **software/** directory and run the provided notebooks.

---

## 🖥️ Running the Simulator  
The Jupyter Notebook includes **forward and inverse kinematics simulations**. Open and execute the notebook in the **software/** directory to visualize deformation patterns.

---

## 🔋 Battery Life & Actuation Cycles  
The **200 mAh battery** provides a theoretical energy capacity of **0.2 × 3.7V = 0.74 Wh**. Under a nominal load, the motor consumes approximately **160 mA × 12V × 1s = 0.000533 Wh** per cycle, yielding a theoretical estimate of **1388 cycles** per full charge.  
However, real-world performance varies due to energy losses, standby consumption, and load fluctuations. Experimental testing with the **XX skeleton configuration** resulted in **XX cycles per full charge**.

---

## 📜 Documentation  
📄 **Paper Reference**: [SoftSnap: Rapid Prototyping of Untethered Soft Robots](LINK_TO_PAPER)  

📜 **CAD & PCB Files**: `/hardware/`  

💻 **Jupyter Notebook Code**: `/software/`  

🛠 **Assembly Guide & Tutorials**: `/docs/`  

🔗 **GitHub Repository**: [GitHub Link](https://github.com/YOUR_GITHUB_USERNAME/SoftSnap)  

---

## 🔬 Citation  
If you use SoftSnap in your research, please cite our work:  

```
@article{zhao2024softsnap,
  title={SoftSnap: Rapid prototyping of untethered soft robots using snap-together modules},
  author={Zhao, Luyang and Jiang, Yitao and She, Chun-Yi and Chen, Muhao and Balkcom, Devin},
  journal={arXiv preprint arXiv:2410.19169},
  year={2024}
}
```

---

## 🔮 Future Work & Contributions  
While this system provides an open-source foundation for soft robotics exploration, we plan to:  
- **Develop a full design/education tool** with optimized skeleton geometries for specific tasks.  
- **Enhance force estimation models** for more advanced control.  
- **Expand simulation capabilities** with real-time physics modeling.  

**Contributions are welcome!** Feel free to submit **pull requests** or report issues.  

---

## 📝 License  
📜 This project is licensed under the **MIT License**.  
