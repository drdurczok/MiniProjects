function a = Acceleration(l, li, phi, omg, eps )
    a = [li(1)*sqrt(eps(1)^2 + omg(1)^4) sqrt( (eps(1)*l(1))^2 + (omg(1)^2*l(1))^2 + (eps(2)*li(2))^2 + (omg(2)^2*li(2))^2 + (eps(1)*l(1)*eps(2)*li(2)  + omg(1)^2*l(1)*omg(2)^2*li(2))*(cos(phi(1)-phi(2))) + (omg(1)^2*l(1)*eps(2)*li(2) + eps(1)*l(1)*omg(2)^2*li(2))*(sin(phi(1)-phi(2))) )];
end














