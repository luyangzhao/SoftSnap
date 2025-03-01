# **SoftSnap Simulation: Forward & Inverse Kinematics**  

## 🏗️ Overview  
This folder contains **Jupyter Notebooks** for simulating SoftSnap’s deformation behavior using **forward and inverse kinematics**. These simulations help visualize how the modular soft robot bends and actuates under different control inputs.

---

## 📂 Files in this Folder  
- `forward_simulation.ipynb` → Simulates how SoftSnap deforms given motor actuation inputs (forward kinematics).  
- `inverse_simulation.ipynb` → Computes the required control inputs to achieve a desired deformation (inverse kinematics).  
- `Firmware.ino` → The firmware program of this project. Use Arduino IDE to edit and burn into the board.  

---

## 🔧 **Installation & Setup**  
To run the simulations, you need **Python 3.x** and Jupyter Notebook installed.  


### **2️⃣ Run the Jupyter Notebook**  
Start Jupyter Notebook and open either `forward_simulation.ipynb` or `inverse_simulation.ipynb`:  
```bash
jupyter notebook
```
Then navigate to the `software/` directory and run the desired notebook.

---

## 📊 **Simulation Details**  

### **🔹 Forward Kinematics (`forward_simulation.ipynb`)**  
- Takes **motor actuation inputs** and computes the resulting deformation of SoftSnap.  
- Helps in understanding how different **threading patterns and actuation sequences** affect movement.  
- Useful for visualizing natural deformations before implementing physical actuation.  

### **🔹 Inverse Kinematics (`inverse_simulation.ipynb`)**  
- Given a **desired deformation shape**, calculates the **necessary motor inputs**.  
- Enables **path planning and motion control** for applications like gripping and locomotion.  
- Helps fine-tune actuation strategies for achieving specific robot configurations.  

---

## 🔬 **Modifications & Customization**  
- To modify simulation parameters, **adjust geometry settings** inside the notebooks.  

For additional documentation, refer to the **SoftSnap project paper**:  
📄 **[SoftSnap: Rapid Prototyping of Untethered Soft Robots](https://arxiv.org/abs/2410.19169)**  

---

## 📜 **License**  
📜 This project is licensed under the **MIT License**.  
