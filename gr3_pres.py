from matplotlib import pyplot as plt

q = input("A number of bodies: ")

option = input("A method of integration('rk4', 'ralston', 'adams', 'rk5', 'adams_10' or 'taylor'): ")
namef_s = f"scalars_{option}({q}).txt"

f1 = open(namef_s, 'r')

dt = []
numerical = []
kepler = []
momentum = []
angular_momentum = []
energy = []
rb = []
vb = []
zero_angular = 0
fl = False

while True:
    line1 = f1.readline()
    if not line1:
        break
    scalars = list(map(float, line1.strip('  ').split()))
    rb.append(scalars[0])
    vb.append(scalars[1])
    momentum.append(scalars[2])
    if fl:
        angular_momentum.append(abs(scalars[3] - zero_angular))
    else:
        zero_angular = scalars[3]
        fl = True
    energy.append(scalars[4]/1e27)
    if q == '2' and option != "taylor":
        dt.append(abs(scalars[5]))

# faceclr = "#800080"
# fig, ax = plt.subplots(2, 3)
# fig.set_size_inches(16, 9)
# plt.subplots_adjust(hspace=0.35)
# fig.set_facecolor(faceclr)
# csfont = {'fontname': 'Segoe UI'}
# plot_clr = "#C2DF38"
# title_clr = "#FFD700"

faceclr = "#003366"
fig, ax = plt.subplots(2, 3)
fig.set_size_inches(16, 9)
plt.subplots_adjust(hspace=0.35)
fig.set_facecolor(faceclr)
csfont = {'fontname': 'Segoe UI'}
plot_clr = "#FFFFFF"
title_clr = "#F0E68C"

momentum = [x - momentum[0] for x in momentum]
ax[0, 0].plot(range(len(momentum)), momentum, color=plot_clr)
ax[0, 0].set_title('momentum', **csfont, color=title_clr, fontsize=13)

# ax[0, 2].set_ylim([-8.5*(1e23-3e27), -7*(1e23-3e27)])
# ax[0, 2].set_ylim(-3.2e-27)
energy = [x - energy[0] for x in energy]
ax[0, 2].plot(range(len(energy)), energy, color=plot_clr)
ax[0, 2].set_title('energy', **csfont, color=title_clr, fontsize=13)

# angular_momentum = [x - angular_momentum[0] for x in angular_momentum]
ax[0, 1].plot(range(len(angular_momentum)), angular_momentum, color=plot_clr)
ax[0, 1].set_title('angular_momentum', **csfont, color=title_clr, fontsize=13)

ax[1, 0].plot(range(len(rb)), rb, color=plot_clr)
ax[1, 0].set_title('barycentre_position(rb)', **csfont, color=title_clr, fontsize=13)

ax[1, 1].plot(range(len(vb)), vb, color=plot_clr)
ax[1, 1].set_title('barycentre_velocity(vb)', **csfont, color=title_clr, fontsize=13)

if q == '2' and option != 'taylor':
    ax[1, 2].plot(range(len(dt)), dt, color=plot_clr)
    ax[1, 2].set_title('d_t', **csfont, color=title_clr, fontsize=13)

for i in range(2):
    for j in range(3):
        ax[i, j].set_facecolor(faceclr)
        ax[i, j].set_xlabel('t', **csfont, color='#FFFFFF', fontsize=13)
        ax[i, j].spines['bottom'].set_color('#FFFFFF')
        ax[i, j].spines['top'].set_color('#FFFFFF')
        ax[i, j].spines['left'].set_color('#FFFFFF')
        ax[i, j].spines['right'].set_color('#FFFFFF')
        ax[i, j].tick_params(axis='x', colors='#FFFFFF')
        ax[i, j].tick_params(axis='y', colors='#FFFFFF')
        # remove spines
        ax[i, j].spines['right'].set_visible(False)
        ax[i, j].spines['top'].set_visible(False)
        # grid
        ax[i, j].set_axisbelow(True)
        # ax[i, j].yaxis.grid(color='#F0E68C', linestyle='dashed', alpha=0.3)
        # ax[i, j].xaxis.grid(color='#F0E68C', linestyle='dashed', alpha=0.3)
        ax[i, j].yaxis.grid(color='#FFFFFF', linestyle='dashed', alpha=0.3)
        ax[i, j].xaxis.grid(color='#FFFFFF', linestyle='dashed', alpha=0.3)

plt.suptitle("The Adams's method 10th order: behavior of invariants", **csfont, color='#F0E68C', fontsize=18)
plt.show()
