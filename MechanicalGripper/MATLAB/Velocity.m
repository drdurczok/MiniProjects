function v = Velocity(l, li, phi, omg)
    v = [omg(1)*li(1) sqrt( (omg(1)*l(1))^2 + (omg(2)*li(2))^2 + 2*omg(1)*omg(2)*l(1)*li(2)*cos(phi(1)-phi(2)))];
end