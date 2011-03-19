<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/">

		<HTML>
			<HEAD>
				<TITLE>Bibtex citations</TITLE>
				<LINK rel="stylesheet" type="text/css" href="stylesheet.css" />
			</HEAD>
			<BODY>
				<xsl:for-each select="citations/article | citations/inproceedings">
					<TABLE border="1" width="80%">
						<TR>
							<TH>Entry Type:</TH>
							<TH><!--<xsl:value-of select="parent::node/data"/>--></TH>
						</TR>						
						<TR>
							<TD>Author</TD>
							<TD><xsl:value-of select="author" /></TD>
						</TR>
						<TR>
							<TD>Title</TD>
							<TD><xsl:value-of select="title"/></TD>
						</TR>
						<TR>
							<TD>Journal</TD>
							<TD><xsl:value-of select="journal" /></TD>
						</TR>
						<TR>
							<TD>Year</TD>
							<TD><xsl:value-of select="year" /></TD>
						</TR>
						<TR>
							<TD>Volume</TD>
							<TD><xsl:value-of select="volume" /></TD>
						</TR>
						<TR>
							<TD>Pages</TD>
							<TD><xsl:value-of select="pages" /></TD>
						</TR>
						<TR>
							<TD>Number</TD>
							<TD><xsl:value-of select="number" /></TD>
						</TR>
						<TR>
							<TD>Month</TD>
							<TD><xsl:value-of select="month" /></TD>
						</TR>
						<TR>
							<TD>DOI</TD>
							<TD><xsl:value-of select="doi" /></TD>
						</TR>
						<TR>
							<TD>Owner</TD>
							<TD><xsl:value-of select="owner" /></TD>
						</TR>
						<TR>
							<TD>Timestamp</TD>
							<TD><xsl:value-of select="timestamp" /></TD>
						</TR>
						
					</TABLE>
					<BR />
				</xsl:for-each>
			</BODY>
		</HTML>
	</xsl:template>

</xsl:stylesheet>