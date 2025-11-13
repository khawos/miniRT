
#!/usr/bin/env python3
"""
Convertisseur de fichiers OBJ vers le format RT pour raytracer
Supporte les triangles et quads (convertis en triangles)
"""

import sys
import os


def parse_obj_file(filepath):
    """Parse un fichier OBJ et retourne les vertices et faces"""
    vertices = []
    faces = []
    
    with open(filepath, 'r') as f:
        for line in f:
            line = line.strip()
            
            # Ignorer les lignes vides et commentaires
            if not line or line.startswith('#'):
                continue
            
            parts = line.split()
            if not parts:
                continue
            
            # Parser les vertices
            if parts[0] == 'v':
                x, y, z = float(parts[1]), float(parts[2]), float(parts[3])
                vertices.append((x, y, z))
            
            # Parser les faces (triangles ou quads)
            elif parts[0] == 'f':
                # Extraire les indices de vertices (format: v, v/vt, v/vt/vn, v//vn)
                face_indices = []
                for vertex_data in parts[1:]:
                    # Prendre seulement l'indice du vertex (avant le premier '/')
                    vertex_index = vertex_data.split('/')[0]
                    # OBJ utilise des indices à partir de 1, on convertit en 0
                    face_indices.append(int(vertex_index) - 1)
                
                faces.append(face_indices)
    
    return vertices, faces


def convert_quad_to_triangles(quad_indices):
    """Convertit un quad en deux triangles"""
    # Quad: [0, 1, 2, 3] -> Triangles: [0, 1, 2] et [0, 2, 3]
    triangle1 = [quad_indices[0], quad_indices[1], quad_indices[2]]
    triangle2 = [quad_indices[0], quad_indices[2], quad_indices[3]]
    return [triangle1, triangle2]


def write_rt_file(vertices, faces, output_filepath, color=(128, 128, 128)):
    """Écrit le fichier RT avec le format spécifié"""
    triangles = []
    
    # Convertir toutes les faces en triangles
    for face in faces:
        if len(face) == 3:
            # Déjà un triangle
            triangles.append(face)
        elif len(face) == 4:
            # Quad, convertir en 2 triangles
            triangles.extend(convert_quad_to_triangles(face))
        else:
            print(f"Attention: Face avec {len(face)} sommets ignorée (seuls triangles et quads sont supportés)")
    
    # Écrire le fichier RT
    with open(output_filepath, 'w') as f:
        for tri in triangles:
            # Récupérer les 3 vertices du triangle
            v1 = vertices[tri[0]]
            v2 = vertices[tri[1]]
            v3 = vertices[tri[2]]
            
            # Format: v1_x,v1_y,v1_z v2_x,v2_y,v2_z v3_x,v3_y,v3_z R,G,B
            line = f"tr {v1[0]},{v1[1]},{v1[2]} {v2[0]},{v2[1]},{v2[2]} {v3[0]},{v3[1]},{v3[2]} {color[0]},{color[1]},{color[2]}\n"
            f.write(line)
    
    print(f"✓ Conversion terminée: {len(triangles)} triangles écrits dans {output_filepath}")


def main():
    if len(sys.argv) < 2:
        print("Usage: python obj_to_rt.py <fichier.obj> [fichier_sortie.rt] [R,G,B]")
        print("Exemple: python obj_to_rt.py model.obj output.rt 200,200,200")
        sys.exit(1)
    
    input_file = sys.argv[1]
    
    # Déterminer le fichier de sortie
    if len(sys.argv) >= 3:
        output_file = sys.argv[2]
    else:
        # Par défaut, même nom avec extension .rt
        output_file = os.path.splitext(input_file)[0] + '.rt'
    
    # Déterminer la couleur
    color = (128, 128, 128)  # Gris par défaut
    if len(sys.argv) >= 4:
        try:
            r, g, b = map(int, sys.argv[3].split(','))
            color = (r, g, b)
        except:
            print("Attention: Format de couleur invalide, utilisation du gris par défaut")
    
    # Vérifier que le fichier existe
    if not os.path.exists(input_file):
        print(f"Erreur: Le fichier '{input_file}' n'existe pas")
        sys.exit(1)
    
    print(f"Lecture du fichier OBJ: {input_file}")
    vertices, faces = parse_obj_file(input_file)
    print(f"✓ {len(vertices)} vertices et {len(faces)} faces trouvés")
    
    print(f"Écriture du fichier RT: {output_file}")
    write_rt_file(vertices, faces, output_file, color)


if __name__ == "__main__":
    main()