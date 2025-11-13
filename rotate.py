#!/usr/bin/env python3
"""
Programme de rotation de formes dans des fichiers RT
Applique une rotation de 90° autour d'un axe choisi
"""

import sys
import os
import math


def parse_rt_line(line):
    """Parse une ligne RT et retourne les données du triangle"""
    line = line.strip()
    if not line.startswith('tr'):
        return None
    
    # Enlever 'tr ' au début
    data = line[3:].strip().split()
    
    if len(data) != 4:
        return None
    
    # Parser les 3 points
    v1 = tuple(map(float, data[0].split(',')))
    v2 = tuple(map(float, data[1].split(',')))
    v3 = tuple(map(float, data[2].split(',')))
    
    # Parser la couleur
    color = data[3]
    
    return v1, v2, v3, color


def rotate_point_x(point, angle_rad):
    """Rotation autour de l'axe X"""
    x, y, z = point
    cos_a = math.cos(angle_rad)
    sin_a = math.sin(angle_rad)
    
    new_y = y * cos_a - z * sin_a
    new_z = y * sin_a + z * cos_a
    
    return (x, new_y, new_z)


def rotate_point_y(point, angle_rad):
    """Rotation autour de l'axe Y"""
    x, y, z = point
    cos_a = math.cos(angle_rad)
    sin_a = math.sin(angle_rad)
    
    new_x = x * cos_a + z * sin_a
    new_z = -x * sin_a + z * cos_a
    
    return (new_x, y, new_z)


def rotate_point_z(point, angle_rad):
    """Rotation autour de l'axe Z"""
    x, y, z = point
    cos_a = math.cos(angle_rad)
    sin_a = math.sin(angle_rad)
    
    new_x = x * cos_a - y * sin_a
    new_y = x * sin_a + y * cos_a
    
    return (new_x, new_y, z)


def rotate_point(point, axis, angle_deg):
    """Applique une rotation à un point"""
    angle_rad = math.radians(angle_deg)
    
    if axis.lower() == 'x':
        return rotate_point_x(point, angle_rad)
    elif axis.lower() == 'y':
        return rotate_point_y(point, angle_rad)
    elif axis.lower() == 'z':
        return rotate_point_z(point, angle_rad)
    else:
        raise ValueError(f"Axe invalide: {axis}. Utilisez 'x', 'y' ou 'z'")


def format_rt_line(v1, v2, v3, color):
    """Formate une ligne RT"""
    return f"tr {v1[0]},{v1[1]},{v1[2]} {v2[0]},{v2[1]},{v2[2]} {v3[0]},{v3[1]},{v3[2]} {color}\n"


def rotate_rt_file(input_file, output_file, axis, angle):
    """Applique une rotation à tous les triangles d'un fichier RT"""
    triangles_processed = 0
    
    with open(input_file, 'r') as f_in, open(output_file, 'w') as f_out:
        for line in f_in:
            parsed = parse_rt_line(line)
            
            if parsed is None:
                # Ligne non-triangle, la copier telle quelle
                f_out.write(line)
                continue
            
            v1, v2, v3, color = parsed
            
            # Appliquer la rotation aux 3 points
            new_v1 = rotate_point(v1, axis, angle)
            new_v2 = rotate_point(v2, axis, angle)
            new_v3 = rotate_point(v3, axis, angle)
            
            # Écrire la ligne transformée
            f_out.write(format_rt_line(new_v1, new_v2, new_v3, color))
            triangles_processed += 1
    
    return triangles_processed


def main():
    if len(sys.argv) < 2:
        print("Usage: python rotate_rt.py <fichier.rt> [axe] [angle] [fichier_sortie.rt]")
        print("\nAxes disponibles: x, y, z (défaut: y)")
        print("Angle en degrés (défaut: 90)")
        print("\nExemples:")
        print("  python rotate_rt.py model.rt              # Rotation de 90° sur Y")
        print("  python rotate_rt.py model.rt x            # Rotation de 90° sur X")
        print("  python rotate_rt.py model.rt y 45         # Rotation de 45° sur Y")
        print("  python rotate_rt.py model.rt z 90 out.rt  # Rotation de 90° sur Z vers out.rt")
        sys.exit(1)
    
    input_file = sys.argv[1]
    
    # Déterminer l'axe
    axis = 'y'
    if len(sys.argv) >= 3:
        axis = sys.argv[2].lower()
        if axis not in ['x', 'y', 'z']:
            print(f"Erreur: Axe '{axis}' invalide. Utilisez 'x', 'y' ou 'z'")
            sys.exit(1)
    
    # Déterminer l'angle
    angle = 90.0
    if len(sys.argv) >= 4:
        try:
            angle = float(sys.argv[3])
        except ValueError:
            print(f"Erreur: Angle invalide '{sys.argv[3]}'")
            sys.exit(1)
    
    # Déterminer le fichier de sortie
    if len(sys.argv) >= 5:
        output_file = sys.argv[4]
    else:
        # Par défaut, ajouter _rotated avant l'extension
        base, ext = os.path.splitext(input_file)
        output_file = f"{base}_rotated{ext}"
    
    # Vérifier que le fichier existe
    if not os.path.exists(input_file):
        print(f"Erreur: Le fichier '{input_file}' n'existe pas")
        sys.exit(1)
    
    print(f"Rotation du fichier: {input_file}")
    print(f"Axe: {axis.upper()}, Angle: {angle}°")
    print(f"Fichier de sortie: {output_file}")
    
    count = rotate_rt_file(input_file, output_file, axis, angle)
    
    print(f"✓ Rotation terminée: {count} triangles transformés")


if __name__ == "__main__":
    main()