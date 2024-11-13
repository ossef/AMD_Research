# AMD_Research
Dynamic Voltage and Frequency Scaling (DVFS) involves
adjusting the speed to match power consumption and performance re-
quirements of the system. This technology has been shown to provide
major power and energy savings in many system components (processor
cores, memory system ...). In this work [1], we study the DVFS mecha-
nism for a processor that implements various levels of speed and power
(we call these levels ”Pstates”). We model the system as a birth-death
process and we compare different configurations, using stochastic com-
parison, in order to evaluate the impact on the response time and power
(and energy) consumption. In the case of two Pstates, we proposed a
closed form for the steady state distribution and we derived a cost func-
tion that uses both performance and energy consumption. Finally, we
derive an algorithm that suggests a threshold which minimizes the cost
function. An extension of this work can be found in [2].

#  Contributors & Copyright

- [Leo LE CORRE](https://github.com/KarmaEssence)
- This code is open source. The original document is [1] or [2].

[1] "Performance evaluation and energy consumption for DVFS processor", Youssef AIT EL MAHJOUB, Hind CASTEL-TALEB and Jean-Michel Fourneau". In the 26th International Conference on Analytical & Stochastic Modelling Techniques & Applications, ASMTA, 2021.

[2] "Performance evaluation of Green IT networks", Youssef AIT EL MAHJOUB. In Phd-thesis, Chapter 3. [link : hal.science](https://hal.science/tel-03215137v1), 2021.
