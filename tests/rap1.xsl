<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html"/>
  
  <!-- Template pour la racine -->
	<xsl:template match="rapport">
		<html>		
			<body>
			<xsl:apply-templates />
			</body>
		</html>
	</xsl:template>

	<!-- Template pour le titre -->
	<xsl:template match="titre">
		<h1>
			<xsl:apply-templates />
		</h1>			
	</xsl:template>

	<!-- Template pour les auteurs -->
	<xsl:template match="auteur">

			<h2>
				Auteur
			</h2>
		<li>
			<xsl:apply-templates />
		</li>			
	</xsl:template>

	<!-- Template pour le resume -->
	<xsl:template match="resume">
		<h2>
			Résumé
		</h2>
		<p>
			<xsl:apply-templates />
		</p>
	</xsl:template>

	<!-- Template pour les chapitres -->
	<xsl:template match="chapitre">		
		<xsl:apply-templates />
	</xsl:template>


</xsl:stylesheet>
