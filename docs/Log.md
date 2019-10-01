# Logbuch 2DGameSDK

## 13.09.2019

### Status

- SceneGraph duale Struktur (tree, map) -> 2h
- AABB und Umrechnung Weltkoordinaten implementiert -> 3h 
  - Irrtum: Umrechnung ist nicht die Inverse Transformation -> +2h
- Kollisionsmasken implementiert -> 4h

### Ausblick

- SceneGraph muss refactored werden (keine Kapselung)
- Vorherzusehende Performance Probleme lösen:
  - Update AABB und Kollisionsmaske max. 1x pro tick (ideal: 1x pro Bewegung)

## 15.09.2019

### Status

- Chopper Demo aktualisiert -> 1h
- Github Kanban Board und Tasks erstellt -> 2h PM

## 16.09.2019

### Status

- SceneGraph Kapselung: Gesamte Logik nun im SceneGraph -> 2h

### Ausblick

- Sollte die Entity SceneGraphNode extenden?
- Sollte der SceneGraph die BewegungsLogik managen?
  - Child Entities würden nur bei Bewegung des Parents aktualisiert werden

## 18.09.2019

### Status

- Kickoff Meeting -> 1h PM
- Kollisionspunkt Berechnung implementiert -> 1h

### Ausblick

- Physik Engine POC
- ~~Kollisionspunkt Berechnung~~
- **Achtung:** Parallele Kanten können noch nicht kollidiert werden

## 20.09.2019

### Status

- Warnings auflösen (`-Wall`, `-Wpedantic`, `-Wextra`) -> 2h
- POC Mit Box2D Physics Engine:
  - Fehlschlag: Direkte Integration Physics im SceneGraph -> 4h
    - Nach 4h konnten noch keine nennenswerte Ergebnisse erzielt werden
      (siehe Branch `Box2dPOC2`)
  - Einfache Physics Engine erstellt -> 1h
    - Dokumentation nicht richtig gelesen (`SetBox`) -> 2h

### Ausblick

- Eine Physics Engine wäre eine hohe Bereicherung der Engine
  - Wall und Entity Collisions über Physik möglich (auch ohne Reaction)
  
- Der Fehlversuch mit dem `SceneGraph` zeigt Schwierigkeiten mit Physics
  - Physikalische Objekte müssen im SceneGraph Top-Level sein
    (unter einander sind sie mit mech. Verbindungen verbunden)
  - Nicht Physikalische `SceneGraph` pseudophysikalisch simulieren
    (mit `body->SetTransform()`)
  - Unteschiedliche Koordinaten Physikal, Visuell
    - Phys. Welt lässt für Objekte einen Range von ca. 0.1m - 10m zu
      Skalierung notwendig
    - Phys. Welt geht vom Mittelpunkt des Objekts aus
    - Phys. Welt ist y+ gegen Oben

## 21.09.2019

### Status

- Chipmunk POC umgesetzt -> 4h

### Ausblick

- Vgl. Chipmnunk Box2D:
  - Beide verwenden Objektzentrische Koordinaten
  - Beide sind ausreichend dokumentiert (Beispiele + Dokumentation)
  - Chipmunk API komfortabler und intuitiver (trotz C..)
  - Box2D bietet mehr Möglichkeiten (e.g. Collision Sensor)
  - Box2D bedingt Skalierung (Bereich: 0.1m-10m)
  - Unterschiedliche Struktur:
    - Box2D: `World > Body > Shape > Fixture` 
    - Chipmunk: `Space > Body > Shape`

## 24.09.2019

### Status

- Entity Refactoring umgesetzt -> 6h
  - Funktion `GetTransformable` gelöscht, bessere Kapselung
  - Neue Funktionen: `Transform`, `SetTransform`, `GetTransform`
  - Entity wird nur aktualisiert wenn Parent oder Entity bewegt wird
  - Kollisionsmasken und AABB können in der Entity gespeichert werden
    und müssen nicht bei jeder Abfrage neu berechnet werden
  - Klasse `TransformableEntity` Speichert alle Transformationen:
    - Transformation der Entity selbst: `Transform`
    - Akkumulierte Transformation der Parents: `AccTransform`
    - Transformation Parents mal Transfomrtaion Ent.: `FullTransform`

### Ausblick

- Fixed Update Funktion?
  - Möglichkeit alle Transformationen einmalig pro Tick zu berechnen
  - Alternativen? (innerhalb Tick möglich da nicht sicher ob ein Parent
    vorher aktualisiert wird, alternativ dies garantieren..)

## 25.09.2019

### Status

- Neues Event `OnTickEnded()` -> 0.5h
  - Aktualisierung Kollision erst nach `Tick()` (vor Kollisionscheck)
- Kanban Tasks aktualisiert -> 0.5h PM

### Ausblick

- **TBD:** Sollte der `GameState` bei jedem `Tick()` mitgegeben werden?
  - Man kann einfache Statusvariablen im State speichern, dies wird 
    vorausgesetzt um die Spiellogik aufzubauen
  - Der `GameState` muss in diesem Fall generisch sein, mit Konsequenz dass
    jedes Spielelemnt (`Scene`, `Entity`, ..) generisch sein muss
  - Alternativ muss der Spielentwickler selbst mit statischen Klassen oder
    globalen Variablen arbeiten

## 29.09.2019

### Status

- Zeitplanung und Arbeit am Pflichtenheft -> 12h PM


## 01.10.2019

### Status

- Prototypes Benchmarking Setup -> 2h
