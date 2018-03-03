function P = PressingForce(m,up_a,horz_a)    
    F = m*(9.81+up_a);      %[N]
    Ff = F/4;               %Friction forces are distributed onto four fingers
    
    P(1) = Ff/0.2;
    P(2) = m*horz_a/2;      %Horizontal forces are distributed onto two fingers
    P(3) = sqrt(P(1)^2 + P(2)^2);    %Force generated per finger [N]
end






