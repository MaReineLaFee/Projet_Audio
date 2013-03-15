vecteur_son=zeros(200,1);
for i=1:200
    vecteur_son(i) = sin(2*pi*200*i*(1/44000));
end

vecteur_son_C = load('vecteur_son.txt');
figure(1); plot(vecteur_son_C)
norme = norm(vecteur_son_C,1);
norme

module_C = load('module.txt');
norme_2eme_spectre = norm(module_C(22051:44100),1)
figure(2); plot(module_C);
figure(3); plot(module_C(22051:44100));
norme_3eme_spectre = norm(module_C(66151:88200),1)
figure(4); plot(module_C(66151:88200));
figure(5); plot(module_C(88200:110255));

module_lisse_C = load('spectre_lisse.txt');
norme_2eme_spectre = norm(module_lisse_C(22051:44100),1)
figure(6); plot(module_lisse_C);
figure(7); plot(module_lisse_C(22051:44100));
norme_3eme_spectre = norm(module_lisse_C(66151:88200),1)
figure(8); plot(module_lisse_C(66151:88200));
figure(9); plot(module_lisse_C(88200:110255));