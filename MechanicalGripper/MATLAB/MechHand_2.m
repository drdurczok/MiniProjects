l = [0.1 0.14];               %[m]
% Starting values
initphi = [0 5];
initomg = [0 0.1];
eps = [115 115];
i = 0;
for t = 0:0.1:1 
    i = i + 1;
    omg = initomg + eps * t;
    phi = initphi + omg * t + 0.5 * eps * t^2;
    
    omg1(i) = omg(1);
    omg2(i) = omg(2);
    phi1(i) = phi(1);
    phi2(i) = phi(2);
    % Angular to linear velocity
    v = Velocity(l,l,phi,omg);
    v1(i) = v(1);
    v2(i) = v(2);
    % Angular to linear acceleration
    a = Acceleration(l,l,phi, omg, eps);
    a1(i) = a(1);
    a2(i) = a(2);
end
t = 0:0.1:1;
figure(1); hold on; plot(t,phi1); plot(t,phi2); title('Change of angle');
xlabel('Time [s]'); ylabel('Change in angle [deg]');
legend('Point B','Point C');

figure(2); subplot(1,2,1); hold on; plot(t,omg1); plot(t,omg2); title('Angular velocity plot');
xlabel('Time [s]'); ylabel('Change in angular velocity [deg/s]');
legend('Point B','Point C');
subplot(1,2,2); hold on; plot(t,v1); plot(t,v2); title('Linear velocity plot');
xlabel('Time [s]'); ylabel('Change in linear velocity [m/s]');
legend('Point B','Point C');

figure(3); hold on; plot(t,a1); plot(t,a2); title('Linear acceleration plot');
xlabel('Time [s]'); ylabel('Change in linear acceleration [m/s^2]');
legend('Point B','Point C');