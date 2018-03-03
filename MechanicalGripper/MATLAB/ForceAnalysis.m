function M = ForceAnalysis(m,lcm,l,n,P)
    G = m*9.81;
    % Friction force
    F = 0.2*P(1);      %[N]
    % Input from servo encoder
    phi = [45 45];    %[deg]
    
    % For static configurations B = [0,0]
    if n == 1   
        B = InertialForce(m,l,lcm,phi);
    end
    if n ~= 1
        B = [0 0];
    end

    A = [1 0 -1 0 0 0; 
        0 -1 0 1 0 0; 
        0 0 sin(phi(1))*l(1) cos(phi(1))*l(1) -1 1; 
        0 0 1 0 0 0; 
        0 0 0 1 0 0; 
        0 0 0 0 0 1];

    C = [-B(1)*sin(phi(1));
        -G(1) + B(1)*cos(phi(1));
        (B(1) - G(1)*cos(phi(1)))*lcm(1);
        -B(2)*sin(phi(2)) + P(3)*sin(phi(2)) - F*cos(phi(2));
        P(3)*cos(phi(2)) + G(2) - B(2)*cos(phi(2)) + F*sin(phi(2));
        P(3)*l(2) - B(2)*lcm(2) + G(2)*cos(phi(2))*lcm(2)];
    %In our calculations, we assumed the force of gravity to be the wrong
    %way, thus we changed the sign for the simulation.
    
    M = A\C;    %[R01x; R01y; R12x; R12y; Mr1; Mr2]

end




