# QubOS
*This is J2050's on-board software (QubOS) source code repository and wiki.*
## 
### What is J2050?
<img src="../imgs/QubOS-J2050logo.jpg" alt="J2050 logo" width="100"/></br>

J2050 is an aerospace student project which is set to be the first student team from the University of Padova (UniPD) to launch a satellite (a 2P PocketQube named "RedPill") into orbit.
Its main objective is to give the participating students a hands-on experience of a space mission and to help them apply what they studied during their courses to a real-life project.
In addition to its educational goal, this mission has the following three main technological objectives:
1) To study the feasibility of non-mechanical space telescope covers.
2) To collect in-situ measurements of the sub-mm space debris environment in LEO.
3) To assess satellite tracking and attitude determination methods through observations of LEDs from the ground and with on-board photodiode data.

### QubOS framework
J2050 adopts FreeRTOS kernel and CMSIS v2 API to support its software, both to ensure compatibility with future UniPD projects that will share the same architecture, and to adopt a solution already tested for university PocketQube projects. 
In fact, the project relies on previous international experiences, whose publications[^1][^2] are a major inspiration and reference for the creation of QubOS. 
The adoption of an RTOS also provides a valuable tool for controlling embedded systems in criticality-prone environments such as satellites.
The C code is written according to known best practices with the intent to produce easily maintainable programs. The main coding environments used are STM32CubeIDE and MATLAB R2023.

[^1]: Nil Rius Fortuny, UPC 2023, “On-board computer software development for PocketQubes”, final degree thesis.
https://upcommons.upc.edu/bitstream/handle/2117/390000/memoria.pdf?sequence=2&amp;isAllowed=y  
[^2]: Bouwmeester J. , TUDelft 2021, “The Architecture of CubeSats and PocketQubes. Towards a Lean and Reliable Implementation of Subsystems and Their Interfaces”, PhD Thesis.
https://pure.tudelft.nl/ws/portalfiles/portal/96183067/2021_08_10_PhD_Thesis_Jasper_BouWmeester.pdf
