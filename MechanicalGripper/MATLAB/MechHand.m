% Const values for our configuration
m = [0.4 0.02];               %[kg]
lcm = [0.05 0.06];            %[m]
l = [0.1 0.14];               %[m]

for i = 0:10
    P = PressingForce(0.5,i,i);     % The analysis returns values 
    M = ForceAnalysis(m,lcm,l,1,P); % combined for all fingers
    M1(i+1) = GearRatio(M(5));
    M2(i+1) = GearRatio(M(6));
end

figure;
hold on;
x = 0:1:10;
plot(x,M1*1000)
plot(x,M2*1000)
title('Plot of motor torque to combined acceleration of held object')
xlabel('Combined Acceleration [m/s^2]')
ylabel('Moments [mNm]')
legend('Torque of base joint motor','Torque of end joint motor')








