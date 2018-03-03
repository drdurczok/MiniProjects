function B = InertialForce(m,l,lcm,phi)
    
    % Inputs from servo encoder
    omg = [1 1];
    eps = [0.1 0.1];

    acm = Acceleration(l,lcm,phi,omg,eps);
    
    B(1) = m(1)*acm(1)*-1;
    B(2) = m(2)*acm(2)*-1;
    
end









