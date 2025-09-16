// ============================================================================
// Exemplo expandido para TCC - Sistema de Zoológico
// Cadeias de especialização com herança pública, protegida e privada.
// ============================================================================

class Animal {};

// -------------------------
// Grupos principais
// -------------------------
class Mamifero : public Animal {};
class Ave : protected Animal {};
class Reptil : private Animal {};
class Peixe : public Animal {};
class Anfibio : protected Animal {};

// -------------------------
// Cadeia de mamíferos
// -------------------------
class Felino : public Mamifero {};
class GrandeFelino : protected Felino {};
class Leao : public GrandeFelino {};
class LeaoAfricano : public Leao {};
class LeaoDoSerengeti : private LeaoAfricano {};

// -------------------------
// Cadeia de aves
// -------------------------
class Passaro : protected Ave {};
class Rapina : public Passaro {};
class Aguia : protected Rapina {};
class AguiaReal : public Aguia {};
class AguiaImperial : private AguiaReal {};

// -------------------------
// Cadeia de répteis
// -------------------------
class Lacertilio : private Reptil {};
class Lagarto : public Lacertilio {};
class Iguana : protected Lagarto {};
class IguanaVerde : public Iguana {};
class IguanaGigante : protected IguanaVerde {};

// -------------------------
// Cadeia de peixes
// -------------------------
class PeixeOssudo : public Peixe {};
class Salmao : protected PeixeOssudo {};
class SalmaoAtlantico : public Salmao {};
class SalmaoDoPacifico : private SalmaoAtlantico {};
class SalmaoGigante : public SalmaoDoPacífico {};

// -------------------------
// Cadeia de anfíbios
// -------------------------
class Anuro : protected Anfibio {};
class Sapo : public Anuro {};
class SapoCururu : protected Sapo {};
class SapoGigante : public SapoCururu {};
class SapoMitologico : private SapoGigante {};

// ============================================================================
// Múltipla herança
// ============================================================================
class AnimalAquatico {};
class AnimalVoador {};

class PatoAquatico : public Sapo, public AnimalAquatico {};
class Dragao : public Reptil, protected AnimalVoador, private AnimalAquatico {};

// ============================================================================
// Recursos e sistemas
// ============================================================================
class Recurso {};
class Jaula : public Recurso {};
class Viveiro : protected Recurso {};
class Aquario : private Recurso {};

class SistemaGerenciamento {};
class SistemaFinanceiro : public SistemaGerenciamento {};
class SistemaVisitantes : private SistemaGerenciamento {};

// ============================================================================
// Zoológicos especializados
// ============================================================================
class Zoologico {};
class ZoologicoUrbano : public Zoologico, public SistemaGerenciamento {};
class ZoologicoRural : protected Zoologico, private SistemaFinanceiro {};
class ZoologicoDigital : public Zoologico, protected SistemaVisitantes {};
class ZoologicoAquatico : public Zoologico, protected AnimalAquatico {};
