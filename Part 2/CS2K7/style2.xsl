<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output
method="html"
omit-xml-declaration="no"
doctype-public="-//W3C//DTD XHTML 1.1 Strict//EN"
doctype-system="http://www.w3.org/TR/xhtml1/Dtd/xhtml1-transitional.dtd"
indent="yes" />

	<xsl:template match="/">
		<html xmlns="http://www.w3.org/1999/xhtml">
			<head>
				<title>Bibtex citations</title>
				<link rel="stylesheet" type="text/css" href="stylesheet.css" />
			</head>
			<body>
				<xsl:for-each select="citations/*">
					<table cellpadding="3" border="2">
						<tr>
							<th>
								<xsl:value-of select ="local-name()"/> entry:
							</th>
							<th>
								<xsl:value-of select="@name"/>
							</th>
						</tr>
						<xsl:for-each select="*">
							<tr>
								<td class="heading"><xsl:value-of select="local-name()"/></td>
								<td><xsl:value-of select="."/></td>
							</tr>
						</xsl:for-each>
					</table>
					<br/>
				</xsl:for-each>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>